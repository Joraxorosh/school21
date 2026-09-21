from dataclasses import dataclass, field
from typing import Any

from web.model.board_web_model import BoardWebModel


@dataclass
class GameWebModel:
    """JSON-представление текущей игры."""

    id: str
    board: BoardWebModel
    finished: bool = field(default=False)

    @staticmethod
    def from_dict(data: Any) -> "GameWebModel":
        if not isinstance(data, dict) or "id" not in data or "board" not in data:
            raise ValueError("Fields 'id' and 'board' are required")
        return GameWebModel(id=str(data["id"]), board=BoardWebModel.from_dict(data["board"]))

    def to_dict(self) -> dict:
        return {"id": self.id, "board": self.board.to_dict(), "finished": self.finished}
