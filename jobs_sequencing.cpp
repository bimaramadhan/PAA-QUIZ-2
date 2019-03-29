#include <stdio.h>

#define MAX 1000

using namespace std;

typedef struct Job {
  char id[MAX];
  int deadline;
  int profit;
} Job;

//fungsi untuk menghitung job mana yang akan diambil berdasar deadline dan profit secara greedy 
void jobSequencingWithDeadline(Job jobs[], int n);

//fungsi mencari nilai terkecil dari dua nilai yang dibandingkan
int minValue(int x, int y) {
  if(x < y) return x;
  return y;
}

int main(void) {
  //variables
  int i, j;

  //jobs with deadline and profit
//  Job jobs[6] = {
//    {"j1", 2,  60},
//    {"j2", 1, 100},
//    {"j3", 3,  20},
//    {"j4", 3,  40},
//    {"j5", 1,  20},
//    {"j6", 4,  50},
//  };


  //jumlah jobs
  printf("Masukkan jumlah job yang diinginkan : ");
  int n;
  scanf("%d", &n);
  Job jobs[n];
  //temp
  Job temp;
  for(int i=0;i<n;i++) {
  	printf("Masukkan id, deadline dan profit job %d secara berurutan (contoh : j1 1 10) : ", i+1);
  	scanf("%s%d%d", &jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
  }

  //sort profit job secara descending (dari profit terbesar)
  for(i = 1; i < n; i++) {
    for(j = 0; j < n - i; j++) {
      if(jobs[j+1].profit > jobs[j].profit) {
        temp = jobs[j+1];
        jobs[j+1] = jobs[j];
        jobs[j] = temp;
      }
    }
  }
  
  //print id job, deadline dan profit yang sudah diurutkan berdasar profit terbesar 
  printf("\n\t%s\t|%s\t|%s\n", "Id Job", "Deadline", "Profit");
  for(i = 0; i < n; i++) {
    printf("\t%s\t|%d\t\t|%d\n", jobs[i].id, jobs[i].deadline, jobs[i].profit);
  }

  //memanggil fungsi untuk menghitung job mana yang akan diambil berdasar deadline dan profit secara greedy 
  jobSequencingWithDeadline(jobs, n);

  return 0;
}

//fungsi untuk menghitung job mana yang akan diambil berdasar deadline dan profit secara greedy 
void jobSequencingWithDeadline(Job jobs[], int n) {
  //variables
  int i, j, k, maxprofit;

  //time slots kosong
  int timeslot[MAX];

  //time slots yang sudah terisi
  int filledTimeSlot = 0;

  //cari nilai deadline maksimal
  int dmax = 0;
  for(i = 0; i < n; i++) {
    if(jobs[i].deadline > dmax) {
      dmax = jobs[i].deadline;
    }
  }

  //time slots yang kosong diinisialisasikan dengan -1 (-1 menandakan kosong/tidak ada isinya)
  for(i = 1; i <= dmax; i++) {
    timeslot[i] = -1;
  }

  printf("\ndmax: %d\n", dmax);
  
  //perulangan untuk memasukkan job ke timeslot yang tersedia
  for(i = 0; i < n; i++) {
    k = minValue(dmax, jobs[i].deadline);
    while(k >= 1) {
      //jika timeslot kosong maka diisi
      if(timeslot[k] == -1) {
        timeslot[k] = i;
        filledTimeSlot++;
        break;
      }
      //jika timeslot sudah terisi decrement k untuk melakukan cek timeslot lain yang belum terisi
      k--;
    }

    //jika semua timeslots sudah terisi maka berhenti
    if(filledTimeSlot == dmax) {
      break;
    }
  }

  //hasil job yang diambil
  printf("\nUrutan Job yang diambil adalah : ");
  for(i = 1; i <= dmax; i++) {
    printf("%s", jobs[timeslot[i]].id);

    if(i < dmax) {
      printf(" --> ");
    }
  }

  //hasil profit
  maxprofit = 0;
  for(i = 1; i <= dmax; i++) {
    maxprofit += jobs[timeslot[i]].profit;
  }
  printf("\nProfit maksimum yang dihasilkan adalah : %d\n", maxprofit);
}
