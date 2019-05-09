#include <iostream>
#include <fstream>

#define MAX 100
#define INF 1000

using namespace std;

int chuaXet[MAX], luuVet[MAX], doDaiDuongDiToi[MAX];

typedef struct DoThi {
	int n;
	int a[MAX][MAX];
} DOTHI;

int timDuongDiNhoNhat(DOTHI g) {
	int li = -1;
	float p = INF;
	for (int i = 0; i < g.n; i++) {
		if (chuaXet[i] == 0 && doDaiDuongDiToi[i] < p) {
			p = doDaiDuongDiToi[i];
			li = i;
		}
	}
	return li;
}

void capNhatDuongDi(int u, DOTHI g) {
	chuaXet[u] = 1;
	for (int v = 0; v < g.n; v++) {
		if (chuaXet[v] == 0 && g.a[u][v] > 0 && g.a[u][v] < INF) {
			if (doDaiDuongDiToi[v] > doDaiDuongDiToi[u] + g.a[u][v]) {
				doDaiDuongDiToi[v] = doDaiDuongDiToi[u] + g.a[u][v];
				luuVet[v] = u;
			}
		}
	}
}

void dijkstra(DOTHI g, int S, int F) {
	for (int i = 0; i < g.n; i++) {
		chuaXet[i] = 0;
		doDaiDuongDiToi[i] = INF;
		luuVet[i] = -1;
	}
	
	doDaiDuongDiToi[S] = 0;
	while (chuaXet[F] == 0) {
		int u = timDuongDiNhoNhat(g);
		if (u == -1) {
			break;
		}
		capNhatDuongDi(u, g);
	}
	if (chuaXet[F] == 1) {
		cout<<"Duong di ngan nhat tu dinh "<<S<<" toi dinh "<<F<<endl;
		int i = F;
		cout<<F;
		while (luuVet[i] != S) {
			cout<<"<-"<<luuVet[i];
			i = luuVet[i];
		}
		cout<<"<-"<<luuVet[i]<<endl;
		cout<<"Do dai duong di: "<<doDaiDuongDiToi[F]<<endl;
	} else {
		cout<<"Khong co duong di nao "<<endl;
	}
}

void nhapFile(DOTHI &g) {
	ifstream fp("dijkstra.txt");
	if (!fp) {
		cout<<"Loi khong the doc file!"<<endl;
		return;
	}
	g.n = 6;
	for (int i = 0; i < g.n; i++) {
		for (int j = 0; j < g.n; j++) {
			fp >> g.a[i][j];
		}
	}
}
int main() {
	DOTHI g;

	nhapFile(g);
	dijkstra(g, 0, 5);
	return 0;
}

