// Operating System II Project
// Disk Scheduling Simulator

// Doha Tariq ElFarghaly
// 2015/13243


#include "pch.h"
#include <iostream>
#include <math.h>
#include <algorithm>
#include <list> 
#include <iterator> 
#include <string>
using namespace std;


void fcfs(int*, int, int, int, int, bool);
void scan(int*, int, int, int, int, bool);
void cscan(int*, int, int, int, int, bool);
void look(int*, int, int, int, int, bool);
void clook(int*, int, int, int, int, bool);
void sstf(int*, int, int, int, int);

int main() {

	cout << "Welcome To Dee's Disk Scheduling Simulator \n" << endl;
	cout << "Please Follow The Following Steps To Finish The Scheduling Mission \n" << endl;

	cout << "I. Please Enter The Head: " << endl;
	int head;
	cin >> head;

	cout << "II. Enter The Limit Of The Disks: " << endl;
	int end;
	cin >> end;

	int reqs_count;
	cout << "III. Enter Number Of Requests: " << endl;
	cin >> reqs_count;

	int* reqs = new int[reqs_count];

	cout << "IV. Enter Requests: " << endl;
	for (int i = 0; i < reqs_count; i++) {
		reqs[i] = end + 1;
		while (reqs[i] > end) {
			cout << i << ": ";
			cin >> reqs[i];
			if (reqs[i] > end) {
				cout << "Please Enter A Valid Number!\n";
			}
		}
	}

	cout << "V. Enter Seek Time: " << endl;
	int seektime;
	cin >> seektime;
	cout << "VI. Choose Direction: ";
	bool upper = false;
	cout << "Please Choose: (1) For Going Right" << " | " << "(0) For Going Left: " << endl;
	cin >> upper;

	int cont = 1;
	while (cont != 0) {

		int algo;

		cout << "VII. Choose One Of The Following Scheduling Algorithms: \n";
		cout << "1 - FCFS\n";
		cout << "2 - SCAN\n";
		cout << "3 - CSCAN\n";
		cout << "4 - LOOK\n";
		cout << "5 - CLOOK\n";
		cout << "6 - SSTF\n";

		cout << endl;
		cout << "Your Choice Is: ";
		cin >> algo;

		switch (algo) {
		case 1:
			fcfs(reqs, head, reqs_count, seektime, end, upper);
			break;
		case 2:
			scan(reqs, head, reqs_count, seektime, end, upper);
			break;
		case 3:
			cscan(reqs, head, reqs_count, seektime, end, upper);
			break;
		case 4:
			look(reqs, head, reqs_count, seektime, end, upper);
			break;
		case 5:
			clook(reqs, head, reqs_count, seektime, end, upper);
			break;
		case 6:
			sstf(reqs, head, reqs_count, seektime, end);
			break;
		dafault:
			cout << "The Choice You Made Isn't Right. Please Choose Carefully.";
		}

		cout << "\n\n If You Are Done, Please Press (0). If You wish To Continue, Please Press (1): " << endl;
		cin >> cont;
		cout << "\n";
	}
}

//FCFS
void fcfs(int* reqs, int head, int reqs_count, int seektime, int end, bool upper) {

	cout << "FCFS: " << endl;
	int ttl_distance = abs(head - reqs[0]);
	for (int i = 0; i < reqs_count - 1; i++) {
		ttl_distance += abs(reqs[i] - reqs[i + 1]);
	}

	cout << "FCFS Order: " << head << " -> ";
	for (int i = 0; i < reqs_count; i++) {
		string arrow = " -> ";
		if (i == reqs_count - 1) {
			arrow = "";
		}
		cout << reqs[i] << arrow;
	}
	cout << "\n" << "FCFS Seek Time: " << ttl_distance << " Cylinders/ " << ttl_distance * seektime << "ms";
	cout << endl << endl;
}

//SCAN
void scan(int* reqs_, int head, int reqs_count, int seektime, int end, bool upper) {
	cout << "SCAN: " << endl;

	int* requests = new int[reqs_count];
	for (int i = 0; i < reqs_count; i++) {
		requests[i] = reqs_[i];
	}

	sort(requests, requests + reqs_count);

	list<int>left;
	list<int>right;

	for (int i = 0; i < reqs_count; i++) {
		if (requests[i] > head)
			right.push_back(requests[i]);
		else
			left.push_back(requests[i]);
	}
	list<int> SCAN_requests;

	SCAN_requests.push_back(head);
	
	for (int i = 0; i < 2; i++)	{
		if (upper) {
			for (list <int> ::iterator i = right.begin(); i != (right.end()); i++) {
				SCAN_requests.push_back(*i);
			}
		}
		else {
			for (auto i = left.rbegin(); i != (left.rend()); i++)
			{
				SCAN_requests.push_back(*i);
			}
		}
		if (i == 0) {
			SCAN_requests.push_back((end - 1) * upper);
		}
		upper = !upper;
	}

	int ttl_distance = 0;
	cout << "SCAN Order: ";
	for (list <int> ::iterator i = SCAN_requests.begin(); i != prev(SCAN_requests.end()); i++) {
		cout << *i << " -> ";
		ttl_distance += abs(*i - *next(i));
	}
	cout << *prev(SCAN_requests.end());
	cout << "\n" << "SCAN Seek Time: " << ttl_distance << " Cylinders/ " << ttl_distance * seektime << "ms";
	cout << endl << endl;
}

//CSCAN
void cscan(int* reqs_, int head, int reqs_count, int seektime, int end, bool upper) {
	cout << "CSCAN: " << endl;

	int* requests = new int[reqs_count];
	for (int i = 0; i < reqs_count; i++) {
		requests[i] = reqs_[i];
	}

	sort(requests, requests + reqs_count);

	list<int>left;
	list<int>right;
	for (int i = 0; i < reqs_count; i++) {
		if (requests[i] > head)
			right.push_back(requests[i]);
		else
			left.push_back(requests[i]);
	}
	list<int> CSCAN_requests;
	CSCAN_requests.push_back(head);

	if (upper) {
		left.reverse();
	}
	else {
		right.reverse();
	}

	for (int i = 0; i < 2; i++)	{
		if (upper) {
			for (list <int> ::iterator i = right.begin(); i != (right.end()); i++) {
				CSCAN_requests.push_back(*i);
			}
		}
		else {
			for (auto i = left.rbegin(); i != (left.rend()); i++) {
				CSCAN_requests.push_back(*i);
			}
		}
		if (i == 0) {
			CSCAN_requests.push_back((end - 1) * upper);
			CSCAN_requests.push_back((end - 1) * !upper);
		}
		upper = !upper;
	}

	int total_distance = 0;

	cout << "CSCAN Order: ";
	for (list <int> ::iterator i = CSCAN_requests.begin(); i != prev(CSCAN_requests.end()); i++) {
		cout << *i << " -> ";
		total_distance += abs(*i - *next(i));

	}
	cout << *prev(CSCAN_requests.end());
	cout << "\n" << "CSCAN Seek Time: " << total_distance << " Cylinders/ " << total_distance * seektime << "ms";
	cout << endl << endl;

}

//LOOK
void look(int* reqs_, int head, int reqs_count, int seektime, int end, bool upper) {
	int* requests = new int[reqs_count];
	for (int i = 0; i < reqs_count; i++) {
		requests[i] = reqs_[i];
	}
	cout << "LOOK: " << endl;
	sort(requests, requests + reqs_count);

	list<int>left;
	list<int>right;
	for (int i = 0; i < reqs_count; i++) {
		if (requests[i] > head)
			right.push_back(requests[i]);
		else
			left.push_back(requests[i]);
	}
	list<int> LOOK_requests;
	LOOK_requests.push_back(head);

	for (int i = 0; i < 2; i++) {
		if (upper) {
			for (list <int> ::iterator i = right.begin(); i != (right.end()); i++) {
				LOOK_requests.push_back(*i);
			}
		}
		else {
			for (auto i = left.rbegin(); i != (left.rend()); i++) {
				LOOK_requests.push_back(*i);
			}
		}
		if (i == 0)
			upper = !upper;
	}

	int total_distance = 0;
	cout << "LOOK Order: ";

	for (list <int> ::iterator i = LOOK_requests.begin(); i != prev(LOOK_requests.end()); i++) {
		cout << *i << " -> ";
		total_distance += abs(*i - *next(i));
	}

	cout << *prev(LOOK_requests.end());
	cout << "\n" << "LOOK Seek Time: " << total_distance << " Cylinders/ " << total_distance * seektime << "ms";
	cout << endl << endl;
}

//CLOOK
void clook(int* reqs_, int head, int reqs_count, int seektime, int end, bool upper) {
	int* requests = new int[reqs_count];
	
	for (int i = 0; i < reqs_count; i++) {
		requests[i] = reqs_[i];
	}

	cout << "CLOOK: " << endl;
	sort(requests, requests + reqs_count);

	list<int>leftt;
	list<int>rightt;
	
	for (int i = 0; i < reqs_count; i++) {
		if (requests[i] > head) 
			rightt.push_back(requests[i]);
		else
			leftt.push_back(requests[i]);
	}
	list<int> CLOOK_requests;
	CLOOK_requests.push_back(head);
	
	if (upper) {
		leftt.reverse();
	}
	else {
		rightt.reverse();
	}

	for (int i = 0; i < 2; i++) {
		if (upper) {
			for (list <int> ::iterator i = rightt.begin(); i != (rightt.end()); i++) {
				CLOOK_requests.push_back(*i);
			}
		}
		else {
			for (auto i = leftt.rbegin(); i != (leftt.rend()); i++) {
				CLOOK_requests.push_back(*i);
			}
		}
		if (i == 0)
			upper = !upper;
	}
	int total_distance = 0;
	cout << "CLOOK Order: ";

	for (list <int> ::iterator i = CLOOK_requests.begin(); i != prev(CLOOK_requests.end()); i++) {
		cout << *i << " -> ";
		total_distance += abs(*i - *next(i));

	}
	cout << *prev(CLOOK_requests.end());
	cout << "\n" << "CLOOK Seek Time: " << total_distance << " Cylinders/ " << total_distance * seektime << "ms";
	cout << endl << endl;
}

//SSTF
void sstf(int* reqs_, int head, int reqs_count, int seektime, int end) {
	cout << "SSTF: " << endl;

	int* requests = new int[reqs_count];
	for (int i = 0; i < reqs_count; i++) {
		requests[i] = reqs_[i];
	}

	int* sstf_requests = new int[reqs_count];
	for (int i = 0; i < reqs_count; i++) {
		sstf_requests[i] = requests[i];
	}
	int current_request = head;
	int current_request_index = -1;
	int least_distance = 999;
	int least_distance_indx = 0;

	for (int i = 0; i < reqs_count; i++) {
		for (int j = 0; j < reqs_count; j++) {
			if (j == current_request_index) {
				continue;
			}
			if (least_distance > abs(current_request - requests[j])) {
				least_distance = abs(current_request - requests[j]);
				least_distance_indx = j;
			}
		}

		least_distance = 999;
		sstf_requests[i] = requests[least_distance_indx];
		current_request = requests[least_distance_indx];
		requests[least_distance_indx] = 999;
	}

	cout << "SSTF Order: ";
	for (int i = 0; i < reqs_count; i++) {
		string arrow = " -> ";
		if (i == reqs_count - 1) {
			arrow = "";
		}
		cout << sstf_requests[i] << arrow;
	}

	int ttl_distance = abs(head - sstf_requests[0]);
		;
	for (int i = 0; i < reqs_count - 1; i++) {
		ttl_distance += abs(sstf_requests[i] - sstf_requests[i + 1]);
	}

	cout << "\n" << "SSTF Seek Time: " << ttl_distance << " Cylinders/ " << ttl_distance * seektime << "ms";
	cout << endl << endl;
}
