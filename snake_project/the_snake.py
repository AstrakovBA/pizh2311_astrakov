import pygame
from random import randint
from typing import List, Tuple

# Константы для размеров поля и сетки:
SCREEN_WIDTH, SCREEN_HEIGHT = 640, 480
GRID_SIZE = 20
GRID_WIDTH = SCREEN_WIDTH // GRID_SIZE
GRID_HEIGHT = SCREEN_HEIGHT // GRID_SIZE

# Направления движения:
UP = (0, -1)
DOWN = (0, 1)
LEFT = (-1, 0)
RIGHT = (1, 0)

# Цвета:
BOARD_BACKGROUND_COLOR = (0, 0, 0)
BORDER_COLOR = (93, 216, 228)
APPLE_COLOR = (255, 0, 0)
SNAKE_COLOR = (0, 255, 0)

# Скорость движения змейки:
SPEED = 20

# Инициализация pygame и создание экрана и часов
pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT), 0, 32)
clock = pygame.time.Clock()


class GameObject:
    """Базовый класс для игровых объектов."""

    def __init__(self, body_color: Tuple[int, int, int] = BOARD_BACKGROUND_COLOR):
        """Инициализирует базовые атрибуты игрового объекта.

        Args:
            body_color: Цвет объекта в формате RGB.
        """
        self.position = (0, 0)
        self.body_color = body_color

    def draw(self, surface: pygame.Surface):
        """Абстрактный метод для отрисовки объекта.

        Args:
            surface: Поверхность для отрисовки.
        """
        raise NotImplementedError(
            'Метод draw должен быть переопределён в подклассе'
        )


class Apple(GameObject):
    """Класс, описывающий яблоко и действия с ним."""

    def __init__(self):
        """Инициализирует яблоко со случайной позицией и красным цветом."""
        super().__init__(APPLE_COLOR)
        self.randomize_position()

    def randomize_position(self, snake_positions: List[Tuple[int, int]] = None):
        """Устанавливает случайное положение яблока на игровом поле.

        Args:
            snake_positions: Список позиций сегментов змейки, чтобы яблоко
                             не появилось на змейке.
        """
        if snake_positions is None:
            snake_positions = []

        while True:
            self.position = (
                randint(0, GRID_WIDTH - 1) * GRID_SIZE,
                randint(0, GRID_HEIGHT - 1) * GRID_SIZE
            )
            if self.position not in snake_positions:
                break

    def draw(self, surface: pygame.Surface):
        """Отрисовывает яблоко на игровой поверхности.

        Args:
            surface: Поверхность для отрисовки.
        """
        rect = pygame.Rect(self.position, (GRID_SIZE, GRID_SIZE))
        pygame.draw.rect(surface, self.body_color, rect)
        pygame.draw.rect(surface, BORDER_COLOR, rect, 1)


class Snake(GameObject):
    """Класс, описывающий змейку и её поведение."""

    def __init__(self):
        """Инициализирует змейку с начальными параметрами."""
        super().__init__(SNAKE_COLOR)
        self.reset()

    def reset(self):
        """Сбрасывает змейку в начальное состояние."""
        self.positions = [((SCREEN_WIDTH // 2), (SCREEN_HEIGHT // 2))]
        self.length = 1
        self.direction = RIGHT
        self.next_direction = None
        self.last = None

    def update_direction(self):
        """Обновляет направление движения змейки."""
        if self.next_direction:
            self.direction = self.next_direction
            self.next_direction = None

    def move(self) -> bool:
        """Обновляет позицию змейки.

        Returns:
            bool: True если змейка столкнулась с собой, иначе False.
        """
        head_x, head_y = self.positions[0]
        dir_x, dir_y = self.direction
        new_x = (head_x + dir_x * GRID_SIZE) % SCREEN_WIDTH
        new_y = (head_y + dir_y * GRID_SIZE) % SCREEN_HEIGHT
        new_position = (new_x, new_y)

        if new_position in self.positions[1:]:
            self.reset()
            return True

        self.positions.insert(0, new_position)
        if len(self.positions) > self.length:
            self.last = self.positions.pop()
        else:
            self.last = None

        return False

    def draw(self, surface: pygame.Surface):
        """Отрисовывает змейку на экране.

        Args:
            surface: Поверхность для отрисовки.
        """
        for position in self.positions[:-1]:
            rect = pygame.Rect(position, (GRID_SIZE, GRID_SIZE))
            pygame.draw.rect(surface, self.body_color, rect)
            pygame.draw.rect(surface, BORDER_COLOR, rect, 1)

        # Отрисовка головы змейки
        head_rect = pygame.Rect(self.positions[0], (GRID_SIZE, GRID_SIZE))
        pygame.draw.rect(surface, self.body_color, head_rect)
        pygame.draw.rect(surface, BORDER_COLOR, head_rect, 1)

        # Затирание последнего сегмента
        if self.last:
            last_rect = pygame.Rect(self.last, (GRID_SIZE, GRID_SIZE))
            pygame.draw.rect(surface, BOARD_BACKGROUND_COLOR, last_rect)

    def get_head_position(self) -> Tuple[int, int]:
        """Возвращает позицию головы змейки.

        Returns:
            Tuple[int, int]: Координаты головы змейки.
        """
        return self.positions[0]


def handle_keys(game_object: Snake):
    """Обрабатывает нажатия клавиш для управления змейкой.

    Args:
        game_object: Объект змейки, которым управляет игрок.
    """
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            raise SystemExit
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP and game_object.direction != DOWN:
                game_object.next_direction = UP
            elif event.key == pygame.K_DOWN and game_object.direction != UP:
                game_object.next_direction = DOWN
            elif event.key == pygame.K_LEFT and game_object.direction != RIGHT:
                game_object.next_direction = LEFT
            elif event.key == pygame.K_RIGHT and game_object.direction != LEFT:
                game_object.next_direction = RIGHT


def main():
    """Основная функция игры, содержащая главный игровой цикл."""
    pygame.display.set_caption('Змейка')

    snake = Snake()
    apple = Apple()
    score = 0

    while True:
        clock.tick(SPEED)
        handle_keys(snake)

        snake.update_direction()
        game_over = snake.move()

        if game_over:
            score = 0
            apple.randomize_position()

        if snake.get_head_position() == apple.position:
            snake.length += 1
            score += 1
            apple.randomize_position(snake.positions)

        screen.fill(BOARD_BACKGROUND_COLOR)
        snake.draw(screen)
        apple.draw(screen)

        # Отображение счёта
        font = pygame.font.SysFont('Arial Black', 20)
        score_text = font.render(f'Счёт: {score}', True, (255, 255, 255))
        screen.blit(score_text, (5, 5))

        pygame.display.update()


if __name__ == '__main__':
    main()