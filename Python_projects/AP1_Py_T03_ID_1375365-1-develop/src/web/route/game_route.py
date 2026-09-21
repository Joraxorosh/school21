from flask import Blueprint, jsonify, request

from web.module.game_controller import GameController


def create_game_blueprint(controller: GameController) -> Blueprint:
    """Регистрирует маршрут POST /game/<UUID> в Flask-блюпринте."""
    blueprint = Blueprint("game", __name__)

    @blueprint.route("/game/<game_id>", methods=["POST"])
    def post_game(game_id: str):
        payload = request.get_json(silent=True)
        if payload is None:
            return jsonify({"error": "Request body must be valid JSON"}), 400

        body, status_code = controller.make_move(game_id, payload)
        return jsonify(body), status_code

    return blueprint
