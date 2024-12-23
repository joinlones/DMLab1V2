#include <iostream>
#include <cmath>

struct figure {
    bool circle;  // 1 - круг, 0 - прямоугольник
    double x0;    // Координата X центра
    double y0;    // Координата Y центра
    double w;     // Ширина (для прямоугольника)
    double h;     // Высота (для прямоугольника)
    double R;     // Радиус (для круга)
};

// Проверка принадлежности точки кругу
bool point_in_circle(double x, double y, const figure& fig) {
    return ((x - fig.x0) * (x - fig.x0) + (y - fig.y0) * (y - fig.y0)) <= fig.R * fig.R;
}

// Проверка принадлежности точки прямоугольнику
bool point_in_rectangle(double x, double y, const figure& fig) {
    return (x >= fig.x0 - fig.w / 2 && x <= fig.x0 + fig.w / 2 &&
        y >= fig.y0 - fig.h / 2 && y <= fig.y0 + fig.h / 2);
}

// Логическая операция пересечения
bool intersection(bool inA, bool inB) {
    return inA && inB;
}

// Логическая операция объединения
bool union_op(bool inA, bool inB) {
    return inA || inB;
}

// Логическая операция дополнения
bool complement(bool inB) {
    return !inB;
}

// Проверка принадлежности точки множеству по формуле: (A ∩ (¬B ∪ D)) ∪ C
bool point_in_set(double x, double y, const figure& A, const figure& B, const figure& C, const figure& D) {
    bool inA = A.circle ? point_in_circle(x, y, A) : point_in_rectangle(x, y, A);
    bool inB = B.circle ? point_in_circle(x, y, B) : point_in_rectangle(x, y, B);
    bool inC = C.circle ? point_in_circle(x, y, C) : point_in_rectangle(x, y, C);
    bool inD = D.circle ? point_in_circle(x, y, D) : point_in_rectangle(x, y, D);

    // Выражение: ((A ∩ ¬B) ∪ D) ∩ C
    return intersection(union_op(intersection(inA, complement(inB)), inD), inC);
}

void input_figure(figure& fig) {
    std::cout << "Введите тип фигуры (1 - круг, 0 - прямоугольник): ";
    std::cin >> fig.circle;

    std::cout << "Введите координаты центра (x0, y0): ";
    std::cin >> fig.x0 >> fig.y0;

    if (fig.circle) {
        std::cout << "Введите радиус круга (R): ";
        std::cin >> fig.R;
        fig.w = fig.h = 0;  // Убираем значения для ширины и высоты, если это круг
    }
    else {
        std::cout << "Введите ширину и высоту прямоугольника (w, h): ";
        std::cin >> fig.w >> fig.h;
        fig.R = 0;  // Убираем радиус, если это прямоугольник
    }
}

int main() {
    figure A, B, C, D;
    double x, y;
    int choice;

    while (true) {
        std::cout << "Меню:\n";
        std::cout << "1. Ввести фигуры\n";
        std::cout << "2. Проверить точку\n";
        std::cout << "3. Выход\n";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Фигура A:\n";
            input_figure(A);
            std::cout << "Фигура B:\n";
            input_figure(B);
            std::cout << "Фигура C:\n";
            input_figure(C);
            std::cout << "Фигура D:\n";
            input_figure(D);
        }
        else if (choice == 2) {
            std::cout << "Введите координаты точки (x, y): ";
            std::cin >> x >> y;
            if (point_in_set(x, y, A, B, C, D)) {
                std::cout << "Точка принадлежит множеству.\n";
            }
            else {
                std::cout << "Точка не принадлежит множеству.\n";
            }
        }
        else if (choice == 3) {
            break;
        }
    }
    return 0;
}