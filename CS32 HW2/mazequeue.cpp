//#include <queue>
//#include <string>
//#include <iostream>
//
//using namespace std;
//
//class Coord
//{
//public:
//    Coord(int r, int c) : m_row(r), m_col(c) {}
//    int r() const { return m_row; }
//    int c() const { return m_col; }
//private:
//    int m_row;
//    int m_col;
//};
//
//bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
//    queue<Coord> coordQueue;
//
//    Coord start(sr, sc);
//    Coord end(er, ec);
//
//    coordQueue.push(start);
//    maze[sr][sc] = 'o';
//
//    while (!coordQueue.empty()) {
//        Coord curr = coordQueue.front();
//        cout << "(" << curr.r() << ", " << curr.c() << ")" << endl;
//        coordQueue.pop();
//
//        if ((curr.r() == end.r()) && (curr.c() == end.c()))
//            return true;
//
//        if (maze[curr.r()][curr.c() + 1] == '.') {              // EAST
//            Coord temp(curr.r(), curr.c() + 1);
//            coordQueue.push(temp);
//            maze[temp.r()][temp.c()] = 'o';
//        }
//
//        if (maze[curr.r() - 1][curr.c()] == '.') {              // NORTH
//            Coord temp(curr.r() - 1, curr.c());
//            coordQueue.push(temp);
//            maze[temp.r()][temp.c()] = 'o';
//        }
//
//        if (maze[curr.r()][curr.c() - 1] == '.') {              // WEST
//            Coord temp(curr.r(), curr.c() - 1);
//            coordQueue.push(temp);
//            maze[temp.r()][temp.c()] = 'o';
//        }
//
//        if (maze[curr.r() + 1][curr.c()] == '.') {              // SOUTH
//            Coord temp(curr.r() + 1, curr.c());
//            coordQueue.push(temp);
//            maze[temp.r()][temp.c()] = 'o';
//        }
//    }
//
//    return false;
//}
//
//int main()
//{
//    string maze[10] = {
//        "XXXXXXXXXX",
//        "X..X...X.X",
//        "X.XXXX.X.X",
//        "X.X.X..X.X",
//        "X...X.XX.X",
//        "XXX......X",
//        "X.X.XXXX.X",
//        "X.XXX....X",
//        "X...X..X.X",
//        "XXXXXXXXXX"
//    };
//
//    if (pathExists(maze, 10, 10, 5, 3, 8, 8))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}