from flask import Flask

from di.container import Container
from web.route.game_route import create_game_blueprint


def create_app() -> Flask:
    app = Flask(__name__)
    container = Container()
    app.register_blueprint(create_game_blueprint(container.game_controller))
    return app


app = create_app()

if __name__ == "__main__":
    app.run(debug=True)
