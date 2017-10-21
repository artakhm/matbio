#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>

const double birth_rate = 0.4;
const double death_rate = 0.2;
const double birth_distance = 0.5;
const double death_distance = 0.5;
int wall = 0;

class Cell {
private:
    long long  population, column;
    double x;
public:
    Cell() {};

    Cell(int Population, double X)
    : population(Population), x(X) {};

    long long get_population() const {
        return population;
    }

    double get_coordinates() const {  // FIXME: for many dimensions need a vector
        return x;
    }

    long long get_indices() const {  // FIXME: for many dimensions need a vector
        return column;
    }

    void set_population(long long Population) {
        population = Population;
    }

    void set_coordinates(double X) {  // FIXME: for many dimensions need a vector
        x = X;
    }

    void set_indices(long long Column) {  // FIXME: for many dimensions need a vector
        column = Column;
    }

    void print(std::ostream &out) const {
        out << std::setw(3) << population << std::endl;
    }

    friend std::ostream &operator<<(std::ostream &out, const Cell &cell) {
        cell.print(out);
        return out;
    }
};

class Grid {
private:
    long long population, discretization;
    double width;  // FIXME: for many dimensions need a vector
    double cell_width;  // FIXME: for many dimensions need a vector
    std::vector<Cell> cells;

public:
    Grid() {};

    Grid(long long Init_population, long long Discretization, double Width)
    :population(Init_population), discretization(Discretization), width(Width) {
        cell_width = width / (double)discretization;
        cells = std::vector<Cell>(discretization);
        for (long long i = 0; i != cells.size(); ++i) {
            cells[i].set_coordinates(width / discretization * i);
            cells[i].set_indices(i);
            cells[i].set_population(0);
        }
        for (long long i = 0; i != population; ++i) {
            long long index = (((long long)rand() << 32) + rand()) % discretization;  // Слабоумие и слабоумие
            cells[index].set_population(cells[index].get_population() + 1);
        }
    }

    long long get_population() const {
        return population;
    }

    long long get_discretization() const {  // FIXME: for many dimensions need a vector
        return discretization;
    }

    double get_size() const {  // FIXME: for many dimensions need a vector
        return width;
    }

    double get_cell_size() const {  // FIXME: for many dimensions need a vector
        return cell_width;
    }

    std::vector<Cell> get_cells() const {  // FIXME: for many dimensions need a vector
        return cells;  // not sure about const to edit with cell.set_value()
    }

    Cell & operator[] (int x) {  // setter
        return cells[x];
    }

    Cell operator[] (int x) const {  // getter
        return cells[x];
    }
};

double distance(const Cell &from, const Cell &to) {  // FIXME: for many dimensions need a vector
    return std::sqrt(std::pow((from.get_coordinates() - to.get_coordinates()), 2));
}

std::vector<Cell> neighbour_influence(const Grid &grid, const Cell &cell, double max_distance = birth_distance) {
    // max_distance ? need func for arbitrary Gaussian distribution expectation and variance
    long long border_x = ceil(max_distance / grid.get_cell_size());  // check for types conversion
    std::vector<Cell> result;
    if (wall == 0) {
        long long left_border  = ((long long)cell.get_indices() - border_x <= 0 ? 0 : cell.get_indices() - border_x);
        long long right_border = ((long long)cell.get_indices() + border_x >= grid.get_discretization() ? grid.get_discretization() : cell.get_indices() + border_x);
        for (long long i = left_border; i != right_border; ++i) {
            result.push_back(grid.get_cells()[i]);
        }
    }
    return result;
}

int main(int argc, char ** argv) {
    srand(time(NULL));
    Grid grid(10, 10, 1);
    for (auto cell : neighbour_birth_influence(grid, grid[0])) {
        std::cout << cell;
    }
}
