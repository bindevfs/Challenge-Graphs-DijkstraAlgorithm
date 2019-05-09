# Challenge-Graphs-DijkstraAlgorithm
 Create a program that finds the shortest path through a graph using its edges.
Cho đồ thị G gồm có n đỉnh và ma trận a, ta tìm đường đi ngắn nhất từ đỉnh S (Start) đến đỉnh F(Finish)
**Mô tả giải thuật:**
1. Khởi tạo tất cả các đỉnh có khoảng cách là ∞ (vô cùng), và đỉnh bắt đầu là bằng 0, lưu lại độ đài dường đi là -1
2. Trong khi đỉnh D vẫn còn chưa xét thì:
  - Chọn đỉnh u vẫn còn thuộc trong các đỉnh chưa xét 
  - Có đỉnh v cũng chưa thuộc trong các đỉnh chưa xét đó nếu D[v] > D[u] + a[u][v] (trong đó D: độ dài đường đi, còn a là mảng 2 chiều) thì D[v] = D[u] + a[u][v] và tiến hành lưu lại độ dài đường đi của đinh u -> v
```C++
#define MAX 100 //giới hạn mảng có độ dài 100
#define INF 1000 //infinity : vô cùng

int chuaXet[MAX]; //đánh dấu đỉnh nào trong dồ thị đã xét rồi và đỉnh nào chưa xét khi duyệt từ S -> F
int luuVet[MAX]; // Lưu lại các đỉnh trên đường đi
int doDaiDuongDiToi[MAX]; // Lưu độ dài đường đi nhỏ nhất khi duyệt từ S -> F
```
**Viết hàm timDuongDiNhoNhat dùng để tìm đường đi đến các đỉnh chưa xét chúng ta sẽ căn cứ vào mảng doDaiDuongDiToi**
```C++
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
```
**Viết hàm capNhatDuongDi để tiến hành cập nhật lại độ dài của đường đi khi tiến hành thực thi thuật toán tại đỉnh u**
```C++
void capNhatDuongDi(int u, DOTHI g) {
	chuaXet[u] = 1;
	for (int v = 0; v < g.n; v++) {
 // Tìm đỉnh v chưa xét và độ dài các cạnh nối từ u -> v
		if (chuaXet[v] == 0 && g.a[u][v] > 0 && g.a[u][v] < INF) { 
			if (doDaiDuongDiToi[v] > doDaiDuongDiToi[u] + g.a[u][v]) {
				doDaiDuongDiToi[v] = doDaiDuongDiToi[u] + g.a[u][v];
				luuVet[v] = u;
			}
		}
	}
}
```
**Viết hàm tìm đườg đi ngắn nhât**
```C++
void dijkstra(DOTHI g, int S, int F) {
	for (int i = 0; i < g.n; i++) {
		chuaXet[i] = 0;
		doDaiDuongDiToi[i] = INF;
		luuVet[i] = -1;
	}
	
	doDaiDuongDiToi[S] = 0;
	while (chuaXet[F] == 0) { //Nếu chưa xét đến đỉnh F thì vòng lặp vẫn tiếp tục
		int u = timDuongDiNhoNhat(g); //Tìm đỉnh có độ dài đường đi nhỏ nhất
		if (u == -1) { //Nếu không có thì dừng chương trình và kết quả là không tìm thấy đường đi
			break;
		}
		capNhatDuongDi(u, g); // cập nhật lại độ dài đường đi hiện tại
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
```
