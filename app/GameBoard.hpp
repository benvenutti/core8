#pragma once

#include <model/CellSystem.hpp>

#include <QColor>
#include <QWidget>

#include <cstddef>

class QPainter;

class GameBoard : public QWidget {
  Q_OBJECT

public:
  explicit GameBoard(QWidget* parent = nullptr);

  auto clear() -> void;
  auto generate() -> void;

  auto color() const -> QColor {
    return m_color;
  }

  auto color(QColor color) -> void {
    m_color = color;
  }

public slots:
  void cycle();

private:
  auto paintEvent(QPaintEvent* event) -> void override;
  auto mousePressEvent(QMouseEvent* event) -> void override;
  auto mouseMoveEvent(QMouseEvent* event) -> void override;

  auto paintGrid(QPainter& painter) -> void;
  auto paintWorld(QPainter& painter) -> void;

  const std::size_t gridSize{ 60 };
  model::CellSystem m_cellSystem;
  QColor m_color;
};
