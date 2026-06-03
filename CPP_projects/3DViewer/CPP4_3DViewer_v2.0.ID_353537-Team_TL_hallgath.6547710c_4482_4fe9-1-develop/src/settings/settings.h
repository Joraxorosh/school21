#pragma once

#include <QJsonObject>

namespace s21 {

	enum class ProjectionType {
		kPerspective = 0,
		kOrthographic = 1
	  };

	struct AppSettings {

		ProjectionType projection = ProjectionType::kPerspective;

		bool fill_enabled = false;
		bool transparent = false;
		float fill_rgba[4] = {0.0f, 1.0f, 1.0f, 1.0f};

		bool draw_edges = true;
		bool edges_dashed = false;
		float edge_rgb[3] = {0.0f, 0.0f, 0.0f};
		float edge_width = 2.0f;
		float dash_period = 0.1f;
		float dash_fill = 0.5f;

		int vertex_mode = 0;
		float vertex_size = 8.0f;
		float vertex_rgb[3] = {0.0f, 0.0f, 1.0f};


		float background_rgb[3] = {1.0f, 1.0f, 1.0f};

		QJsonObject ToJson() const;
		static AppSettings FromJson(const QJsonObject& settings_json);

		static AppSettings Load();
		static bool Save(const AppSettings& settings);
	};
}