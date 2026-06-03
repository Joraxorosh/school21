#include "gl_widget.h"

namespace s21 {
namespace {
inline void NormalizeAngle(double& a) {
  while (a >= 360.0) a -= 360.0;
  while (a < 0.0) a += 360.0;
}
}  // namespace

GlWidget::GlWidget(QWidget* parent) : QOpenGLWidget(parent), params_{} {
  setFocusPolicy(Qt::StrongFocus);

  params_.fill_enabled = false;
  params_.draw_edges = true;

  params_.edge_rgb[0] = 0.f;
  params_.edge_rgb[1] = 0.f;
  params_.edge_rgb[2] = 0.f;
  params_.edge_width = 1.f;

  params_.transparent = false;

  params_.edges_dashed = false;
  params_.dash_period = 0.15f;
  params_.dash_fill = 0.5f;

  params_.vertex_mode = 0;  // 0 нет, 1 круг, 2 квадрат
  params_.vertex_size = 6.f;
  params_.vertex_rgb[0] = 0.f;
  params_.vertex_rgb[1] = 0.f;
  params_.vertex_rgb[2] = 0.f;

  params_.fill_rgba[0] = 0.f;   // красный
  params_.fill_rgba[1] = 0.f;   // зеленый
  params_.fill_rgba[2] = 1.f;   // синий!
  params_.fill_rgba[3] = 0.8f;  // прозрачность

  params_.background_rgb[0] = 0.92f;
  params_.background_rgb[1] = 0.92f;
  params_.background_rgb[2] = 0.92f;

  params_.dash_period = 0.05f;
  params_.dash_fill = 0.50f;

  LoadSettings();

  gif_recorder_ = new GifRecorder(this);

  connect(gif_recorder_, &s21::GifRecorder::gifSaved, this,
          &s21::GlWidget::GifSaved);

  connect(&timer_, &QTimer::timeout, this, [this]() {
    TickInput();
    update();
  });
  timer_.start(16);
}

GlWidget::~GlWidget() {
  makeCurrent();
  render_.Destroy();
  doneCurrent();
}

void GlWidget::SetFillOpaque(bool opaque) {
  params_.fill_rgba[3] = opaque ? 1.0f : 0.99f;
  params_.transparent = !opaque;
  SaveSettings();
  update();
}

void GlWidget::SetFillAlpha(float a) {
  params_.fill_rgba[3] = std::clamp(a, 0.0f, 1.0f);

  if (params_.fill_rgba[3] < 0.999f) {
    fill_alpha_saved_ = params_.fill_rgba[3];
  }
  SaveSettings();
  update();
}

static bool LoadObjToMeshData(const std::string& filename,
                              s21::GlRender::MeshData& out) {
  std::vector<s21::Vertex> v;
  std::vector<s21::Edge> e;
  std::vector<std::uint32_t> t;

  if (!s21::ObjParser::Parse(filename, v, e, t)) return false;

  out.vertices_xyz.clear();
  out.edge_indices.clear();
  out.tri_indices.clear();

  out.vertices_xyz.reserve(v.size() * 3);
  for (const auto& p : v) {
    out.vertices_xyz.push_back(static_cast<float>(p.x));
    out.vertices_xyz.push_back(static_cast<float>(p.y));
    out.vertices_xyz.push_back(static_cast<float>(p.z));
  }

  out.edge_indices.reserve(e.size() * 2);
  for (const auto& ed : e) {
    out.edge_indices.push_back(static_cast<std::uint32_t>(ed.first));
    out.edge_indices.push_back(static_cast<std::uint32_t>(ed.second));
  }

  out.tri_indices = std::move(t);
  return true;
}

void GlWidget::initializeGL() {
  initializeOpenGLFunctions();

  if (!render_.Initialize(this)) {
    qWarning() << "GlRender Initialize failed";
    return;
  }

  render_ready_ = true;

  const QString path = "parser/examples/airboat.obj";
  LoadObjToMeshData(path.toStdString(), mesh_);
  render_.UploadMesh(mesh_);

  model_file_name_ = QFileInfo(path).fileName();
  model_vertex_count_ = static_cast<int>(mesh_.vertices_xyz.size() / 3);
  model_edge_count_ = static_cast<int>(mesh_.edge_indices.size() / 2);

  emit ModelInfoChanged(model_file_name_, model_vertex_count_,
                        model_edge_count_);
}

bool GlWidget::LoadModelFromObjFile(const QString& path) {
  if (path.isEmpty()) return false;

  s21::GlRender::MeshData new_mesh;
  if (!LoadObjToMeshData(path.toStdString(), new_mesh)) {
    return false;
  }

  mesh_ = std::move(new_mesh);

  if (render_ready_) {
    makeCurrent();
    render_.UploadMesh(mesh_);
    doneCurrent();

    model_file_name_ = QFileInfo(path).fileName();
    model_vertex_count_ = static_cast<int>(mesh_.vertices_xyz.size() / 3);
    model_edge_count_ = static_cast<int>(mesh_.edge_indices.size() / 2);

    emit ModelInfoChanged(model_file_name_, model_vertex_count_,
                          model_edge_count_);
  }

  update();
  return true;
}

void GlWidget::resizeGL(int w, int h) { render_.Resize(w, h); }

void GlWidget::paintGL() {
  UpdateMvp();
  render_.Render(mvp_col_major_, params_);

  if (gif_recorder_ && gif_recorder_->isRecording()) {  // gif
    const QImage frame = grabFramebuffer();
    if (!frame.isNull()) {
      gif_recorder_->captureFrame(frame);
    }
  }
}

void GlWidget::keyPressEvent(QKeyEvent* e) {
  if (!e->isAutoRepeat()) keys_.insert(e->key());

  if (!e->isAutoRepeat()) {
    if (e->key() == Qt::Key_P) ToggleProjection();
    if (e->key() == Qt::Key_Z) ToggleFill();
  }
  QOpenGLWidget::keyPressEvent(e);
}

void GlWidget::keyReleaseEvent(QKeyEvent* e) {
  if (!e->isAutoRepeat()) keys_.remove(e->key());
  QOpenGLWidget::keyReleaseEvent(e);
}

void GlWidget::TickInput() {
  bool changed = false;
  const double rot_step = 1.0;
  const double move_step = 0.05;

  if (keys_.contains(Qt::Key_I)) {
    ax_ += rot_step;
    changed = true;
  }
  if (keys_.contains(Qt::Key_K)) {
    ax_ -= rot_step;
    changed = true;
  }
  if (keys_.contains(Qt::Key_J)) {
    ay_ += rot_step;
    changed = true;
  }
  if (keys_.contains(Qt::Key_L)) {
    ay_ -= rot_step;
    changed = true;
  }
  if (keys_.contains(Qt::Key_U)) {
    az_ += rot_step;
    changed = true;
  }
  if (keys_.contains(Qt::Key_O)) {
    az_ -= rot_step;
    changed = true;
  }
  const double zoom_k = 0.98;

  if (proj_mode_ == ProjectionMode::kPerspective) {
    if (keys_.contains(Qt::Key_W)) {
      cam_z_ -= move_step;
      changed = true;
    }
    if (keys_.contains(Qt::Key_S)) {
      cam_z_ += move_step;
      changed = true;
    }
  } else {
    if (keys_.contains(Qt::Key_W)) {
      ortho_half_w_ *= zoom_k;
      changed = true;
    }
    if (keys_.contains(Qt::Key_S)) {
      ortho_half_w_ /= zoom_k;
      changed = true;
    }
  }

  if (keys_.contains(Qt::Key_A)) {
    cam_x_ -= move_step;
    changed = true;
  }
  if (keys_.contains(Qt::Key_D)) {
    cam_x_ += move_step;
    changed = true;
  }
  if (keys_.contains(Qt::Key_Q)) {
    cam_y_ -= move_step;
    changed = true;
  }
  if (keys_.contains(Qt::Key_E)) {
    cam_y_ += move_step;
    changed = true;
  }

  if (cam_z_ < 0.2) cam_z_ = 0.2;

  if (changed) {
    NormalizeAngles();
    emit RotationChanged(ax_, ay_, az_);
  }
}

void GlWidget::NormalizeAngles() {
  NormalizeAngle(ax_);
  NormalizeAngle(ay_);
  NormalizeAngle(az_);
}

void GlWidget::ToggleProjection() {  // тип проекции
  proj_mode_ = (proj_mode_ == ProjectionMode::kPerspective)
                   ? ProjectionMode::kOrtho
                   : ProjectionMode::kPerspective;
  SaveSettings();
  update();
}

void GlWidget::ToggleFill() {
  params_.fill_enabled = !params_.fill_enabled;
  emit FillEnabledChanged(params_.fill_enabled);
  SaveSettings();
  update();
}

void GlWidget::UpdateMvp() {
  const double aspect =
      (height() == 0)
          ? 1.0
          : (static_cast<double>(width()) / static_cast<double>(height()));
  const S21Matrix Rx = s21::AffineTransformation::GetRotationXMatrix(ax_);
  const S21Matrix Ry = s21::AffineTransformation::GetRotationYMatrix(ay_);
  const S21Matrix Rz = s21::AffineTransformation::GetRotationZMatrix(az_);
  const S21Matrix R = Rz * (Ry * Rx);

  S21Matrix S(4, 4);
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j) S(i, j) = 0.0;
  S(0, 0) = scale_;
  S(1, 1) = scale_;
  S(2, 2) = scale_;
  S(3, 3) = 1.0;

  const S21Matrix M = R * S;

  const S21Matrix V =
      s21::AffineTransformation::Translation4(-cam_x_, -cam_y_, -cam_z_);

  S21Matrix P(4, 4);
  if (proj_mode_ == ProjectionMode::kPerspective) {
    P = s21::Projection::Perspective(fov_y_deg_, aspect, 0.1, 100.0);

  } else {
    const double half_w = ortho_half_w_;
    const double half_h = ortho_half_w_ / aspect;
    P = s21::Projection::OrthoSymmetric(half_w, half_h, 0.1, 100.0);
  }

  const S21Matrix MVP = P * (V * M);

  mvp_col_major_ = s21::AffineTransformation::GetColMajor(MVP);
}

// interface

void GlWidget::SetBackgroundColor(const QColor& c) {
  params_.background_rgb[0] = c.redF();
  params_.background_rgb[1] = c.greenF();
  params_.background_rgb[2] = c.blueF();
  SaveSettings();
  update();
}

void GlWidget::SetProjectionType(int type) {
  proj_mode_ =
      (type == 1) ? ProjectionMode::kPerspective : ProjectionMode::kOrtho;
  SaveSettings();
  update();
}

void GlWidget::SetEdgesDashed(bool on) {
  params_.edges_dashed = on;
  SaveSettings();
  update();
}

void GlWidget::SetEdgeWidth(float w) {
  params_.edge_width = w;
  SaveSettings();
  update();
}

void GlWidget::SetEdgeColor(const QColor& c) {
  params_.edge_rgb[0] = c.redF();
  params_.edge_rgb[1] = c.greenF();
  params_.edge_rgb[2] = c.blueF();
  SaveSettings();
  update();
}

void GlWidget::SetVertexMode(int mode) {
  params_.vertex_mode = mode;
  SaveSettings();
  update();
}

void GlWidget::SetVertexSize(float s) {
  params_.vertex_size = s;
  SaveSettings();
  update();
}

void GlWidget::SetVertexColor(const QColor& c) {
  params_.vertex_rgb[0] = c.redF();
  params_.vertex_rgb[1] = c.greenF();
  params_.vertex_rgb[2] = c.blueF();
  SaveSettings();
  update();
}
void GlWidget::SetDashPeriod(float p) {
  params_.dash_period = std::max(p, 1e-4f);
  SaveSettings();
  update();
}

void GlWidget::SetDashFill(float f) {
  params_.dash_fill = std::clamp(f, 0.05f, 0.95f);
  SaveSettings();
  update();
}

void GlWidget::SetFillEnabled(bool on) {
  if (params_.fill_enabled == on) return;
  params_.fill_enabled = on;
  emit FillEnabledChanged(on);
  SaveSettings();
  update();
}

void GlWidget::SetFillColor(const QColor& c, float a) {
  params_.fill_rgba[0] = c.redF();
  params_.fill_rgba[1] = c.greenF();
  params_.fill_rgba[2] = c.blueF();
  params_.fill_rgba[3] = std::clamp(a, 0.0f, 1.0f);
  SaveSettings();
  update();
}

GlWidget::RotationDeg GlWidget::GetRotationDegrees() const {
  return RotationDeg{ax_, ay_, az_};
}

void GlWidget::SetRotationDegrees(double ax_deg, double ay_deg, double az_deg) {
  ax_ = ax_deg;
  ay_ = ay_deg;
  az_ = az_deg;
  NormalizeAngles();
  update();
}

void GlWidget::ResetRotation() {
  ax_ = 0.0;
  ay_ = 0.0;
  az_ = 0.0;
  NormalizeAngles();
  update();
}

void GlWidget::SetScale(double s) {
  s = std::clamp(s, 0.001, 1000.0);
  if (std::abs(scale_ - s) < 1e-12) return;
  scale_ = s;
  emit ScaleChanged(scale_);
  update();
}

void GlWidget::ScaleBy(double k) {
  if (k <= 0.0) return;
  SetScale(scale_ * k);
}

void GlWidget::ResetScale() { SetScale(1.0); }

void GlWidget::LoadSettings() {
  const AppSettings settings = AppSettings::Load();

  proj_mode_ = (settings.projection == ProjectionType::kPerspective)
                   ? ProjectionMode::kPerspective
                   : ProjectionMode::kOrtho;

  params_.fill_enabled = settings.fill_enabled;
  params_.transparent = settings.transparent;
  for (int i = 0; i < 4; ++i) {
    params_.fill_rgba[i] = settings.fill_rgba[i];
  }

  params_.draw_edges = settings.draw_edges;
  params_.edges_dashed = settings.edges_dashed;
  for (int i = 0; i < 3; ++i) {
    params_.edge_rgb[i] = settings.edge_rgb[i];
  }
  params_.edge_width = settings.edge_width;
  params_.dash_period = settings.dash_period;
  params_.dash_fill = settings.dash_fill;

  params_.vertex_mode = settings.vertex_mode;
  params_.vertex_size = settings.vertex_size;
  for (int i = 0; i < 3; ++i) {
    params_.vertex_rgb[i] = settings.vertex_rgb[i];
  }

  for (int i = 0; i < 3; ++i) {
    params_.background_rgb[i] = settings.background_rgb[i];
  }
}

void GlWidget::SaveSettings() const {
  AppSettings settings;

  settings.projection = (proj_mode_ == ProjectionMode::kPerspective)
                            ? ProjectionType::kPerspective
                            : ProjectionType::kOrthographic;

  settings.fill_enabled = params_.fill_enabled;
  settings.transparent = params_.transparent;
  for (int i = 0; i < 4; ++i) {
    settings.fill_rgba[i] = params_.fill_rgba[i];
  }

  settings.draw_edges = params_.draw_edges;
  settings.edges_dashed = params_.edges_dashed;
  for (int i = 0; i < 3; ++i) {
    settings.edge_rgb[i] = params_.edge_rgb[i];
  }
  settings.edge_width = params_.edge_width;
  settings.dash_period = params_.dash_period;
  settings.dash_fill = params_.dash_fill;

  settings.vertex_mode = params_.vertex_mode;
  settings.vertex_size = params_.vertex_size;
  for (int i = 0; i < 3; ++i) {
    settings.vertex_rgb[i] = params_.vertex_rgb[i];
  }
  for (int i = 0; i < 3; ++i) {
    settings.background_rgb[i] = params_.background_rgb[i];
  }

  AppSettings::Save(settings);
}
int GlWidget::GetProjectionType() const {
  return (proj_mode_ == ProjectionMode::kPerspective) ? 1 : 0;
}

bool GlWidget::GetEdgesDashed() const { return params_.edges_dashed; }

float GlWidget::GetEdgeWidth() const { return params_.edge_width; }

float GlWidget::GetDashPeriod() const { return params_.dash_period; }

float GlWidget::GetDashFill() const { return params_.dash_fill; }

int GlWidget::GetVertexMode() const { return params_.vertex_mode; }

float GlWidget::GetVertexSize() const { return params_.vertex_size; }

bool GlWidget::GetFillTransparent() const {
  return params_.transparent || (params_.fill_rgba[3] < 0.999f);
}

float GlWidget::GetFillAlpha() const { return params_.fill_rgba[3]; }
bool GlWidget::StartGifRecording(const QString& filename) {  // gif
  if (!gif_recorder_) return false;
  if (gif_recorder_->isRecording()) return false;
  if (filename.isEmpty()) return false;

  gif_recorder_->startRecording(filename);
  return true;
}

void GlWidget::StopGifRecording() {  // gif
  if (gif_recorder_) gif_recorder_->stopRecording();
}

bool GlWidget::IsGifRecording() const {  // gif
  return gif_recorder_ && gif_recorder_->isRecording();
}
}  // namespace s21
