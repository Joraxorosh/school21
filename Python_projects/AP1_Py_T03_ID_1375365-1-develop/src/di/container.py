from datasource.repository.game_repository_impl import GameRepositoryImpl
from datasource.service.game_service_impl import GameServiceImpl
from datasource.storage.game_storage import GameStorage
from web.module.game_controller import GameController


class Container:
    """Описывает граф зависимостей приложения."""

    def __init__(self):
        self.game_storage = GameStorage()  # единственный экземпляр хранилища (singleton)
        self.game_repository = GameRepositoryImpl(self.game_storage)
        self.game_service = GameServiceImpl(self.game_repository)
        self.game_controller = GameController(self.game_service)
