/*
ID: mcshen99
LANG: JAVA
TASK: lasers
*/
#include <fstream>
#include <queue>
#include <list>
#include <vector>

using namespace std;

const int infinity = 1000000;

int main() {
		ifstream f("lasers.in");
		ofstream out("lasers.out");

		int N;
		f >> N;
		int fences[100002][2]; //0 is the laser, N + 1 is the barn
		int x, y, a, b;
		f >> x >> y >> a >> b;
		fences[0][0] = x;
		fences[0][1] = y;
		fences[N + 1][0] = a;
		fences[N + 1][1] = b;
		for (int i = 1; i <= N; ++i) {
			int m, n;
			f >> m >> n;
			fences[i][0] = m;
			fences[i][1] = n;
		}

		//if same x or same y then adjmatrix = true, else 0. then shortest path algorithm.
		bool adjMatrix[100002][100002];
		for (int i = 0; i < N + 2; ++i) {
			for (int j = 0; j < N + 2; ++j) {
				if (fences[i][0] == fences[j][0] || fences[i][1] == fences[j][1]) {
					adjMatrix[i][j] = true;
				} else {
					adjMatrix[i][j] = false;
				}
			}
		}

		int[] distances = new int[N + 2];
		boolean[] visited = new boolean[N + 2];

		for (int i = 0; i < N + 2; ++i) {
			distances[i] = INFINITY;
			visited[i] = false;
		}

		distances[0] = 0;
		//        System.out.println(Arrays.toString(distances));
		for (int i = 0; i < N + 2; ++i) {
			int minDist = INFINITY + 1;
			int closestUnvisited = -1;
			for (int j = 0; j < N + 2; ++j) {
				if (!visited[j] && minDist > distances[j]) {
					closestUnvisited = j;
					minDist = distances[j];
				}
			}

			//            System.out.println(closestUnvisited);
			//            System.out.println(minDist);
			visited[closestUnvisited] = true;

			for (int j = 0; j < N + 2; ++j) {
				if (adjMatrix[closestUnvisited][j]) {
					//                    System.out.println(closestUnvisited + " " + j);
					if (distances[closestUnvisited] + 1 < distances[j]) {
						distances[j] = distances[closestUnvisited] + 1;
					}
				}
			}
			//            System.out.println(Arrays.toString(distances));
		}

		if (distances[N + 1] >= INFINITY) {
			distances[N + 1] = 0;
		}
		out.println(distances[N + 1] - 1);
		out.close();
		System.exit(0);
	}
