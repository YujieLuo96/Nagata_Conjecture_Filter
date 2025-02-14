// Online C++ compiler to run C++ program online
#include <iostream>

using namespace std;

int diff(int a) { return a * a - a; }

int minarray(int a[], int n) {
  int min = a[0];
  for (int i = 1; i < n; i++) {
    if (a[i] < min) {
      min = a[i];
    }
  }
  return min;
}

int diffn(int a, int dim) {
  return ((dim - 1) * a - 2) * (a - 1);
} // the difference of right term

void init(int *arr, int k) {
  for (int i = 0; i < k; i++) {
    arr[i] = 0;
  }
} // initialize the array

void print(int *arr, int k) {

  cout << "[ ";
  for (int i = 0; i < k; i++) {
    cout << arr[i] << " ";
  }
  cout << "]" << endl;
} // print array

bool positive(int a) {
  if (a >= 0) {
    return 1;
  } else {
    return 0;
  }
}

bool degree_condition1(int a, int d, int g, int dim) {
  // if (d < 0 || g < 0) {
  //   cout << "invalid d or g" << endl;
  // }
  if (0 < a && a <= d - 1 && diff(a) <= diffn(d, dim) - 2 * g) {
    return 1;
  } else {
    return 0;
  }
}

bool degree_condition2(int *arr, int d, int dim) {
  if (d < 0) {
    cout << "invalid d" << endl;
  }
  int sum = 0;
  for (int i = 0; i < dim + 1; i++) {
    sum += arr[i];
  }
  if (sum > (dim - 1) * d) {
    return 0;
  }
  return 1;
}

bool recurr(int *p, int k0, int *q, int k, int qs, int M, int N, int d, int dim,
            int g) {
  // cout << "d is: " << d << endl;
  // cout << "is working, current array is" << endl;
  // print(p,k0);
  // cout << "current M, N are " << M << " "<< N << endl;
  if (M < 0 || N < 0) {
    cout << "M or N less than zero" << endl;
    return 0;
  }
  int arrt[dim];
  init(arrt, dim);
  for (int i = 0; i < dim + 1; i++) {
    arrt[i] = p[i];
  }
  if (degree_condition1(p[0], d, g, dim) == 0 ||
      degree_condition2(arrt, d, dim) == 0) {
    // cout << "failed1"<< " "<< M << " "<< N << endl;
    return 0;
  }
  if (M == 0 && N == 0) {
    cout << "degree is:" << d << " ";
    print(p, k0);
    return 0;
  }
  if (k == 1) {
    if (M == diff(N) && N <= qs) {
      q[0] = N;
      cout << "degree is:" << d << " ";
      print(p, k0);
      return 0;
    } else {
      // cout << "failed2" << " "<< M << " " << "" << N << " "<< k << "array is:
      // "<< endl; print(p,k0);
      return 0;
    }
  }
  for (; q[0] <= qs && diff(q[0]) <= M && q[0] <= N; q[0]++) {
    init(&q[1], k - 1);
    recurr(p, k0, &q[1], k - 1, q[0], M - diff(q[0]), N - q[0], d, dim, g);
  }
  return 0;
}

void solution(int selfints, int k, int g, int dim) {
  int d, range;
  range = 100; // set the upperbound for degree d that you wanna calculate
  int arr[k];
  int M;
  int N;
  for (d = 2; d <= range; d++) {
    M = diffn(d, dim) - 2 * g;
    N = 2 * g - 2 + selfints + (dim + 1) * d;
    init(arr, k);
    arr[0] = max(selfints + 2, d / (dim + 1));
    recurr(arr, k, arr, k, N, M, N, d, dim, g);
  }
}

int main() {
  int n, g, k, dim;
  n = 1; // set n here
  g = 1; // m=n+2g-2, set g here
  k = 9+n+g;
  dim = 3; // set k here, number of possible coordinates
  cout << "the dimension is: " << dim << endl;
  cout << "the negative intersection number is: " << n << endl;
  cout << "the genus of curve is: " << g << endl;
  cout << "the number of blow-up points is: " << k << endl;
  solution(n, k, g, dim);
  return 0;
}
