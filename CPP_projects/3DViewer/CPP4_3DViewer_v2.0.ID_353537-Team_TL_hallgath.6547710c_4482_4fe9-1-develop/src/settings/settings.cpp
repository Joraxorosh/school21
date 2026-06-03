#include "settings.h"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QStandardPaths>

namespace s21 {
	namespace {
		QString GetSettingsFilePath() {
		  const QString settings_directory =
		      QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

		  QDir().mkpath(settings_directory);
		  return QDir(settings_directory).filePath("settings.json");
		}

		QJsonArray MakeJsonArray3(const float values[3]) {
		  return QJsonArray{values[0], values[1], values[2]};
		}

		QJsonArray MakeJsonArray4(const float values[4]) {
		  return QJsonArray{values[0], values[1], values[2], values[3]};
		}

	}

	QJsonObject AppSettings::ToJson() const {
	  QJsonObject settings_json;

	  settings_json["projection"] =
	      (projection == ProjectionType::kPerspective) ? "perspective" : "orthographic";

	  settings_json["fill_enabled"] = fill_enabled;
	  settings_json["transparent"] = transparent;
	  settings_json["fill_rgba"] = MakeJsonArray4(fill_rgba);

	  settings_json["draw_edges"] = draw_edges;
	  settings_json["edges_dashed"] = edges_dashed;
	  settings_json["edge_rgb"] = MakeJsonArray3(edge_rgb);
	  settings_json["edge_width"] = edge_width;
	  settings_json["dash_period"] = dash_period;
	  settings_json["dash_fill"] = dash_fill;

	  settings_json["vertex_mode"] = vertex_mode;
	  settings_json["vertex_size"] = vertex_size;
	  settings_json["vertex_rgb"] = MakeJsonArray3(vertex_rgb);

	  settings_json["background_rgb"] = MakeJsonArray3(background_rgb);

	  return settings_json;
	}

	AppSettings AppSettings::FromJson(const QJsonObject& settings_json) {
	  AppSettings settings;

	  const QString projection_name =
	      settings_json.value("projection").toString("perspective").toLower();

	  if (projection_name == "orthographic" ||
	      projection_name == "ortho" ||
	      projection_name == "parallel") {
	    settings.projection = ProjectionType::kOrthographic;
	  } else {
	    settings.projection = ProjectionType::kPerspective;
	  }

	  settings.fill_enabled =
	      settings_json.value("fill_enabled").toBool(settings.fill_enabled);
	  settings.transparent =
	      settings_json.value("transparent").toBool(settings.transparent);

	  {
	    const QJsonArray fill_rgba_json = settings_json.value("fill_rgba").toArray();

	    settings.fill_rgba[0] = static_cast<float>(fill_rgba_json.at(0).toDouble(settings.fill_rgba[0]));
	    settings.fill_rgba[1] = static_cast<float>(fill_rgba_json.at(1).toDouble(settings.fill_rgba[1]));
	    settings.fill_rgba[2] = static_cast<float>(fill_rgba_json.at(2).toDouble(settings.fill_rgba[2]));
	    settings.fill_rgba[3] = static_cast<float>(fill_rgba_json.at(3).toDouble(settings.fill_rgba[3]));
	  }

	  settings.draw_edges =
	      settings_json.value("draw_edges").toBool(settings.draw_edges);
	  settings.edges_dashed =
	      settings_json.value("edges_dashed").toBool(settings.edges_dashed);

	  {
	    const QJsonArray edge_rgb_json = settings_json.value("edge_rgb").toArray();

	    settings.edge_rgb[0] = static_cast<float>(edge_rgb_json.at(0).toDouble(settings.edge_rgb[0]));
	    settings.edge_rgb[1] = static_cast<float>(edge_rgb_json.at(1).toDouble(settings.edge_rgb[1]));
	    settings.edge_rgb[2] = static_cast<float>(edge_rgb_json.at(2).toDouble(settings.edge_rgb[2]));
	  }

	  settings.edge_width = static_cast<float>(
	      settings_json.value("edge_width").toDouble(settings.edge_width));
	  settings.dash_period = static_cast<float>(
	      settings_json.value("dash_period").toDouble(settings.dash_period));
	  settings.dash_fill = static_cast<float>(
	      settings_json.value("dash_fill").toDouble(settings.dash_fill));

	  settings.vertex_mode =
	      settings_json.value("vertex_mode").toInt(settings.vertex_mode);
	  settings.vertex_size = static_cast<float>(
	      settings_json.value("vertex_size").toDouble(settings.vertex_size));

	  {
	    const QJsonArray vertex_rgb_json = settings_json.value("vertex_rgb").toArray();

	    settings.vertex_rgb[0] = static_cast<float>(vertex_rgb_json.at(0).toDouble(settings.vertex_rgb[0]));
	    settings.vertex_rgb[1] = static_cast<float>(vertex_rgb_json.at(1).toDouble(settings.vertex_rgb[1]));
	    settings.vertex_rgb[2] = static_cast<float>(vertex_rgb_json.at(2).toDouble(settings.vertex_rgb[2]));
	  }

	  {
	    const QJsonArray background_rgb_json =
	        settings_json.value("background_rgb").toArray();

	    settings.background_rgb[0] =
	        static_cast<float>(background_rgb_json.at(0).toDouble(settings.background_rgb[0]));
	    settings.background_rgb[1] =
	        static_cast<float>(background_rgb_json.at(1).toDouble(settings.background_rgb[1]));
	    settings.background_rgb[2] =
	        static_cast<float>(background_rgb_json.at(2).toDouble(settings.background_rgb[2]));
	  }

	  return settings;
	}

	AppSettings AppSettings::Load() {
	  const QString settings_file_path = GetSettingsFilePath();

	  QFile settings_file(settings_file_path);
	  if (!settings_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
	    return AppSettings{};
	  }

	  const QByteArray json_bytes = settings_file.readAll();
	  settings_file.close();

	  QJsonParseError json_parse_error{};
	  const QJsonDocument json_document =
	      QJsonDocument::fromJson(json_bytes, &json_parse_error);

	  if (json_parse_error.error != QJsonParseError::NoError || !json_document.isObject()) {
	    return AppSettings{};
	  }

	  return AppSettings::FromJson(json_document.object());
	}

	bool AppSettings::Save(const AppSettings& settings) {
	  const QString settings_file_path = GetSettingsFilePath();

	  QFile settings_file(settings_file_path);
	  if (!settings_file.open(QIODevice::WriteOnly |
	                          QIODevice::Truncate |
	                          QIODevice::Text)) {
	    return false;
	  }

	  const QJsonObject settings_json = settings.ToJson();
	  const QJsonDocument json_document(settings_json);
	  const QByteArray json_bytes = json_document.toJson(QJsonDocument::Indented);

	  const qint64 written_bytes = settings_file.write(json_bytes);
	  settings_file.close();

	  return written_bytes == json_bytes.size();
	}
}