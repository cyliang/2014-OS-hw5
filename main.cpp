#include <cstdio>
#include <list>
#include <map>
using namespace std;

#define MAX_CASE 4
int frame_case[MAX_CASE] = {2, 128, 256, 512};

typedef unsigned long address;

int main() {
	char trace_path[100];
	printf("Trace file: ");
	scanf("%100s", trace_path);

	printf("%12s%12s%12s%20s\n", "size", "miss", "hit", "page fault ratio");
	FILE *trace_file = fopen(trace_path, "r");
	for(int test_case = 0; test_case < MAX_CASE; test_case++) {
		list<address> l;
		map<address, list<address>::iterator> h;
		int hit = 0, miss = 0;

		address addr;
		rewind(trace_file);
		while(fscanf(trace_file, "%lx", &addr) != EOF) {
			addr >>= 12;

			if(h.count(addr)) {
				hit++;
				l.erase(h[addr]);
			} else {
				miss++;
				if(l.size() == frame_case[test_case]) {
					h.erase(l.back());
					l.pop_back();
				}
			}
			l.push_front(addr);
			h[addr] = l.begin();
		}

		printf("%12d%12d%12d%20.9lf\n", frame_case[test_case], miss, hit, miss / (double) (hit + miss));
	}

	fclose(trace_file);
	return 0;
}
