from abc import ABC, abstractmethod

from domain.model.game import Game


class GameService(ABC):
    """Контракт бизнес-логики игры в крестики-нолики против компьютера."""

    @abstractmethod
    def get_next_move(self, game: Game) -> Game:
        """Вычислить следующий ход компьютера (Минимакс) и вернуть обновлённую игру."""
        raise NotImplementedError

    @abstractmethod
    def validate_board(self, game: Game) -> bool:
        """Проверить, что присланное поле — допустимое продолжение сохранённой игры."""
        raise NotImplementedError

    @abstractmethod
    def is_game_over(self, game: Game) -> bool:
        """Проверить, завершена ли игра (победа или ничья)."""
        raise NotImplementedError
