#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <initializer_list>

#include "../core/affine_transformation.h"
#include "../core/matrix.h"

namespace {

constexpr double kEps = 1e-9;

void ExpectMatrixNear(const S21Matrix& a, const S21Matrix& b,
                      double eps = kEps) {
  ASSERT_EQ(a.get_rows(), b.get_rows());
  ASSERT_EQ(a.get_cols(), b.get_cols());
  for (int i = 0; i < a.get_rows(); ++i) {
    for (int j = 0; j < a.get_cols(); ++j) {
      EXPECT_NEAR(a(i, j), b(i, j), eps)
          << "Mismatch at (" << i << "," << j << ")";
    }
  }
}

S21Matrix MakePoints3xN(std::initializer_list<s21::Vec3> pts) {
  const int n = static_cast<int>(pts.size());
  S21Matrix m(3, n);
  int j = 0;
  for (const auto& p : pts) {
    m(0, j) = p.x;
    m(1, j) = p.y;
    m(2, j) = p.z;
    ++j;
  }
  return m;
}

s21::Vec3 GetPoint(const S21Matrix& m, int j) {
  return {m(0, j), m(1, j), m(2, j)};
}

s21::Vec3 Sub(const s21::Vec3& a, const s21::Vec3& b) {
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

double SqNorm(const s21::Vec3& v) { return v.x * v.x + v.y * v.y + v.z * v.z; }

// Локальные функции теста
S21Matrix ExpandTo4xN(const S21Matrix& x3xN) {
  const int n = x3xN.get_cols();
  S21Matrix out(4, n);
  for (int j = 0; j < n; ++j) {
    out(0, j) = x3xN(0, j);
    out(1, j) = x3xN(1, j);
    out(2, j) = x3xN(2, j);
    out(3, j) = 1.0;
  }
  return out;
}

S21Matrix ShrinkTo3xN(const S21Matrix& x4xN) {
  const int n = x4xN.get_cols();
  S21Matrix out(3, n);
  for (int j = 0; j < n; ++j) {
    out(0, j) = x4xN(0, j);
    out(1, j) = x4xN(1, j);
    out(2, j) = x4xN(2, j);
  }
  return out;
}

// Rx/Ry/Rz и знаков.
S21Matrix ReferenceRotateBBoxCenter(const S21Matrix& vertices3xN, double ox_deg,
                                    double oy_deg, double oz_deg) {
  const int n = vertices3xN.get_cols();

  double minx = vertices3xN(0, 0), maxx = vertices3xN(0, 0);
  double miny = vertices3xN(1, 0), maxy = vertices3xN(1, 0);
  double minz = vertices3xN(2, 0), maxz = vertices3xN(2, 0);

  for (int j = 1; j < n; ++j) {
    minx = std::min(minx, vertices3xN(0, j));
    maxx = std::max(maxx, vertices3xN(0, j));
    miny = std::min(miny, vertices3xN(1, j));
    maxy = std::max(maxy, vertices3xN(1, j));
    minz = std::min(minz, vertices3xN(2, j));
    maxz = std::max(maxz, vertices3xN(2, j));
  }

  const s21::Vec3 c{(minx + maxx) / 2.0, (miny + maxy) / 2.0,
                    (minz + maxz) / 2.0};

  const S21Matrix Rx = s21::AffineTransformation::GetRotationXMatrix(ox_deg);
  const S21Matrix Ry = s21::AffineTransformation::GetRotationYMatrix(oy_deg);
  const S21Matrix Rz = s21::AffineTransformation::GetRotationZMatrix(oz_deg);

  S21Matrix out(3, n);
  for (int j = 0; j < n; ++j) {
    const s21::Vec3 p = GetPoint(vertices3xN, j);
    const s21::Vec3 q = Sub(p, c);

    const s21::Vec3 q1{Rx(0, 0) * q.x + Rx(0, 1) * q.y + Rx(0, 2) * q.z,
                       Rx(1, 0) * q.x + Rx(1, 1) * q.y + Rx(1, 2) * q.z,
                       Rx(2, 0) * q.x + Rx(2, 1) * q.y + Rx(2, 2) * q.z};
    const s21::Vec3 q2{Ry(0, 0) * q1.x + Ry(0, 1) * q1.y + Ry(0, 2) * q1.z,
                       Ry(1, 0) * q1.x + Ry(1, 1) * q1.y + Ry(1, 2) * q1.z,
                       Ry(2, 0) * q1.x + Ry(2, 1) * q1.y + Ry(2, 2) * q1.z};
    const s21::Vec3 q3{Rz(0, 0) * q2.x + Rz(0, 1) * q2.y + Rz(0, 2) * q2.z,
                       Rz(1, 0) * q2.x + Rz(1, 1) * q2.y + Rz(1, 2) * q2.z,
                       Rz(2, 0) * q2.x + Rz(2, 1) * q2.y + Rz(2, 2) * q2.z};

    const s21::Vec3 p2{c.x + q3.x, c.y + q3.y, c.z + q3.z};
    out(0, j) = p2.x;
    out(1, j) = p2.y;
    out(2, j) = p2.z;
  }
  return out;
}

}  // namespace

TEST(AffineTransformation, Identity4_IsCorrect) {
  const S21Matrix I = s21::AffineTransformation::Identity4();
  ASSERT_EQ(I.get_rows(), 4);
  ASSERT_EQ(I.get_cols(), 4);

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      const double expected = (i == j) ? 1.0 : 0.0;
      EXPECT_NEAR(I(i, j), expected, kEps);
    }
  }
}

TEST(AffineTransformation, Identity3_IsCorrect) {
  const S21Matrix I = s21::AffineTransformation::Identity3();
  ASSERT_EQ(I.get_rows(), 3);
  ASSERT_EQ(I.get_cols(), 3);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      const double expected = (i == j) ? 1.0 : 0.0;
      EXPECT_NEAR(I(i, j), expected, kEps);
    }
  }
}

TEST(AffineTransformation, Translation4_IsCorrect) {
  const double dx = 1.25, dy = -2.5, dz = 0.0;
  const S21Matrix T = s21::AffineTransformation::Translation4(dx, dy, dz);
  const S21Matrix I = s21::AffineTransformation::Identity4();

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (j == 3 && i < 3) continue;
      EXPECT_NEAR(T(i, j), I(i, j), kEps);
    }
  }
  EXPECT_NEAR(T(0, 3), dx, kEps);
  EXPECT_NEAR(T(1, 3), dy, kEps);
  EXPECT_NEAR(T(2, 3), dz, kEps);
  EXPECT_NEAR(T(3, 3), 1.0, kEps);
}

TEST(AffineTransformation, MoveObject_ZeroShift_NoChange) {
  const S21Matrix X = MakePoints3xN({{1, 2, 3}, {-4, 5, -6}, {0, 0, 0}});
  const S21Matrix Y = s21::AffineTransformation::MoveObject(X, 0.0, 0.0, 0.0);
  ExpectMatrixNear(Y, X);
}

TEST(AffineTransformation, MoveObject_ShiftsAllPoints) {
  const S21Matrix X = MakePoints3xN({{1, 2, 3}, {-4, 5, -6}});
  const S21Matrix Y = s21::AffineTransformation::MoveObject(X, 3.0, -2.0, 1.0);

  for (int j = 0; j < X.get_cols(); ++j) {
    EXPECT_NEAR(Y(0, j), X(0, j) + 3.0, kEps);
    EXPECT_NEAR(Y(1, j), X(1, j) - 2.0, kEps);
    EXPECT_NEAR(Y(2, j), X(2, j) + 1.0, kEps);
  }
}

TEST(AffineTransformation, RotationX_90deg_ActsAsExpected) {
  const S21Matrix Rx = s21::AffineTransformation::GetRotationXMatrix(90.0);

  const s21::Vec3 v{0, 1, 0};  // -> (0,0,1)
  const s21::Vec3 r{Rx(0, 0) * v.x + Rx(0, 1) * v.y + Rx(0, 2) * v.z,
                    Rx(1, 0) * v.x + Rx(1, 1) * v.y + Rx(1, 2) * v.z,
                    Rx(2, 0) * v.x + Rx(2, 1) * v.y + Rx(2, 2) * v.z};

  EXPECT_NEAR(r.x, 0.0, 1e-7);
  EXPECT_NEAR(r.y, 0.0, 1e-7);
  EXPECT_NEAR(r.z, 1.0, 1e-7);
}

TEST(AffineTransformation, RotationY_90deg_ActsAsExpected) {
  const S21Matrix Ry = s21::AffineTransformation::GetRotationYMatrix(90.0);

  const s21::Vec3 v{1, 0, 0};  // -> (0,0,-1)
  const s21::Vec3 r{Ry(0, 0) * v.x + Ry(0, 1) * v.y + Ry(0, 2) * v.z,
                    Ry(1, 0) * v.x + Ry(1, 1) * v.y + Ry(1, 2) * v.z,
                    Ry(2, 0) * v.x + Ry(2, 1) * v.y + Ry(2, 2) * v.z};

  EXPECT_NEAR(r.x, 0.0, 1e-7);
  EXPECT_NEAR(r.y, 0.0, 1e-7);
  EXPECT_NEAR(r.z, -1.0, 1e-7);
}

TEST(AffineTransformation, RotationZ_90deg_ActsAsExpected) {
  const S21Matrix Rz = s21::AffineTransformation::GetRotationZMatrix(90.0);

  const s21::Vec3 v{1, 0, 0};  // -> (0,1,0)
  const s21::Vec3 r{Rz(0, 0) * v.x + Rz(0, 1) * v.y + Rz(0, 2) * v.z,
                    Rz(1, 0) * v.x + Rz(1, 1) * v.y + Rz(1, 2) * v.z,
                    Rz(2, 0) * v.x + Rz(2, 1) * v.y + Rz(2, 2) * v.z};

  EXPECT_NEAR(r.x, 0.0, 1e-7);
  EXPECT_NEAR(r.y, 1.0, 1e-7);
  EXPECT_NEAR(r.z, 0.0, 1e-7);
}

TEST(AffineTransformation, Stretch_MultipliesAllElements) {
  const S21Matrix X = MakePoints3xN({{1, 2, 3}, {-4, 5, -6}});
  const double rate = -2.0;

  const S21Matrix Y = s21::AffineTransformation::Stretch(X, rate);

  ASSERT_EQ(Y.get_rows(), X.get_rows());
  ASSERT_EQ(Y.get_cols(), X.get_cols());

  for (int i = 0; i < X.get_rows(); ++i) {
    for (int j = 0; j < X.get_cols(); ++j) {
      EXPECT_NEAR(Y(i, j), X(i, j) * rate, kEps);
    }
  }
}

TEST(AffineTransformation,
     RotateBy_MatchesReferenceAndPreservesDistancesToCenter) {
  const S21Matrix X = MakePoints3xN({{0, 0, 0},
                                     {2, 0, 0},
                                     {2, 2, 0},
                                     {0, 2, 0},
                                     {0, 0, 2},
                                     {2, 0, 2},
                                     {2, 2, 2},
                                     {0, 2, 2}});

  const double ox = 90.0, oy = 0.0, oz = 0.0;

  const S21Matrix Y = s21::AffineTransformation::RotateBy(X, ox, oy, oz);
  const S21Matrix Ref = ReferenceRotateBBoxCenter(X, ox, oy, oz);
  ExpectMatrixNear(Y, Ref, 1e-7);

  const s21::Vec3 c{1, 1, 1};
  for (int j = 0; j < X.get_cols(); ++j) {
    const double d0 = SqNorm(Sub(GetPoint(X, j), c));
    const double d1 = SqNorm(Sub(GetPoint(Y, j), c));
    EXPECT_NEAR(d0, d1, 1e-7);
  }
}

TEST(AffineTransformation, ModelRotateAroundCenter4_IsConsistentWithRotateBy) {
  const S21Matrix X = MakePoints3xN({{0, 0, 0},
                                     {2, 0, 0},
                                     {2, 2, 0},
                                     {0, 2, 0},
                                     {0, 0, 2},
                                     {2, 0, 2},
                                     {2, 2, 2},
                                     {0, 2, 2}});

  const double ox = 10.0, oy = -20.0, oz = 30.0;

  const S21Matrix M =
      s21::AffineTransformation::ModelRotateAroundCenter4(X, ox, oy, oz);
  ASSERT_EQ(M.get_rows(), 4);
  ASSERT_EQ(M.get_cols(), 4);

  const S21Matrix Y1 = s21::AffineTransformation::RotateBy(X, ox, oy, oz);

  const S21Matrix X4 = ExpandTo4xN(X);
  const S21Matrix Y4 = M * X4;
  const S21Matrix Y2 = ShrinkTo3xN(Y4);

  ExpectMatrixNear(Y2, Y1, 1e-7);
}

TEST(AffineTransformation, GetColMajor_MatchesDefinition) {
  S21Matrix M(4, 4);
  double v = 1.0;
  for (int r = 0; r < 4; ++r) {
    for (int c = 0; c < 4; ++c) {
      M(r, c) = v;
      v += 1.0;
    }
  }

  const auto out = s21::AffineTransformation::GetColMajor(M);

  for (int r = 0; r < 4; ++r) {
    for (int c = 0; c < 4; ++c) {
      const float expected = static_cast<float>(M(r, c));
      EXPECT_FLOAT_EQ(out[c * 4 + r], expected)
          << "at (r=" << r << ", c=" << c << ")";
    }
  }
}