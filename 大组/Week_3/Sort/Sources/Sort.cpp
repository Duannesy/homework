#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

#include<assert.h>
#define swap(x,y) x=x+y,y=x-y,x=x-y//����궨���˽����������淽������
#define RADIX 10 //������������ר�� 
using namespace std;
void BubbleSortflag(int arr[], int n){//ð������ʹ�ñ���ж��Ƿ��Ѿ��ź�ʵ�ּ�֦�� 
	bool bExchange = false; // ������־

	for (int i = 0; i < n - 1; i++) // �����n-1������ 
	{
		bExchange = false;
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j + 1], arr[j]);
				bExchange = true; // �����˽������ʽ�������־��Ϊ��
			}
		}

		if (!bExchange) // ������һ������δ�������������������������ǰ��ֹ�㷨
			return;
	}
}
void BubbleSortlast(int arr[], int n){//ð�������ڱ���Ż������ϣ���¼���һ�ν���λ�ã�ʵ�ֿ��ٶ�λ�Ż��� 
	int i = 0;
	int flag = 0;
	int pos = 0;//������¼���һ�ν�����λ��
	int k = n - 1;
	for (i = 0; i < n - 1; i++)//ȷ����������
	{
		pos = 0;
		int j = 0;
		flag = 0;
		for (j = 0; j < k; j++)//ȷ���Ƚϴ���
		{
			if (arr[j]>arr[j + 1])
			{
				//����
				swap(arr[j],arr[j+1]);
				flag = 1;//������
				pos = j;//����Ԫ�أ���¼���һ�ν�����λ��
			}
		}
		if (flag == 0)//���û�н�����Ԫ�أ����Ѿ�����
		{
			return;
		}
		k = pos;//��һ�αȽϵ���¼λ�ü���
	}
}
void BubbleSortdouble(int arr[], int len){//ð��������ǰ�����Ż������ϣ�����˫��ð���Ż���

	int i = 0;
	int j = 0;
	int n = 0;//ͬʱ�����ֵ����С��Ҫ�����±����
	int flag = 0;
	int pos = 0;//������¼���һ�ν�����λ��
	int k = len - 1;
	for (i = 0; i < len - 1; i++)//ȷ����������
	{
		pos = 0;
		flag = 0;
		//����Ѱ�����ֵ
		for (j = n; j < k; j++)//ȷ���Ƚϴ���
		{
			if (arr[j]>arr[j + 1])
			{
				//����
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = 1;//������
				pos = j;//����Ԫ�أ���¼���һ�ν�����λ��
			}
		}
		if (flag == 0)//���û�н�����Ԫ�أ����Ѿ�����,ֱ�ӽ���
		{
			return;
		}
		k = pos;//��һ�αȽϵ���¼λ�ü���
		//����Ѱ����Сֵ
		for (j = k; j > n; j--)
		{
			int tmp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = tmp;
			flag = 1;
		}
		n++;
		if (flag == 0)//���û�н�����Ԫ�أ����Ѿ�����,ֱ�ӽ���
		{
			return;
		}
	}
}
void insertSort(int arr[], int n) {//�������� 
	int i, j, temp;
	for (i = 1; i < n; i++) {
		temp = arr[i];

		for (j = i; j > 0 && arr[j - 1] > temp; j--)
			arr[j] = arr[j - 1]; // ��������Ԫ�������Ųλ

		arr[j] = temp; // ����
	}
}
void merge(int arr[], int L, int M, int R) { 
    int LEFT_SIZE = M - L + 1;
    int RIGHT_SIZE = R - M;
    int left[LEFT_SIZE];
    int right[RIGHT_SIZE];
    int i, j, k;
    // �� M Ϊ�ָ��ߣ���ԭ����ֳ�����������
    for (i = L; i <= M; i++) left[i - L] = arr[i];
    for (i = M + 1; i <= R; i++) right[i - M - 1] = arr[i];
    // �ٺϲ���һ���������飨������������ѡ����Сֵ���β��룩
    i = 0; j = 0; k = L;
    while (i < LEFT_SIZE && j < RIGHT_SIZE) arr[k++] = left[i] < right[j] ? left[i++] : right[j++];
    while (i < LEFT_SIZE) arr[k++] = left[i++];
    while (j < RIGHT_SIZE) arr[k++] = right[j++];
}

void merge_sort(int arr[], int L, int R) {//�鲢����
    if (L == R) return;
    // �� arr[L..R] ƽ��Ϊ arr[L..M] �� arr[M+1..R]
    int M = (L + R) / 2;
    // �ֱ�ݹ�ؽ�����������Ϊ��������
    merge_sort(arr, L, M);
    merge_sort(arr, M + 1, R);
    // �������������������ٹ鲢�� arr
    merge(arr, L, M, R);
}
void quickSort(int arr[], int begin, int end){
//��������δ�Ż� 

	int i, j, t, pivot;
	if (begin > end) // �ݹ飬ֱ��start = endΪֹ
		return;

	pivot = arr[begin]; // ��׼��
	i = begin;
	j = end;
	while (i != j)
	{
		// ���������ұȻ�׼��С���� ��Ҫ�ȴ��ұ߿�ʼ�ң�
		while (arr[j] >= pivot && i < j)
			j--;
		// ���������ұȻ�׼�������
		while (arr[i] <= pivot && i < j)
			i++;
		if (i < j)
		{
			// �����������������е�λ��
			t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
		}
	}

	// ���ս���׼����λ
	arr[begin] = arr[i];
	arr[i] = pivot;
	quickSort(arr, begin, i - 1); // ����������ߵģ�������һ���ݹ�Ĺ���
	quickSort(arr, i + 1, end); // ���������ұߵ� ��������һ���ݹ�Ĺ���
}
int get_max(int a[], int n) {
	int i, max;
	max = a[0];
	for (i = 1; i < n; i++) {
		if (a[i] > max) {
			max = a[i];
		}
	}
	return max;//��ȡ���ֵ���� 
}
void counting_sort(int a[], int len) {//�������� 
	//ͨ��max��min�������ʱ��������Ҫ���ٵĿռ��С
	int max = a[0], min = a[0];
	for (int i = 0; i < len; i++){
		if (a[i] > max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}
	//ʹ��calloc�����鶼��ʼ��Ϊ0
	int range = max - min + 1;
	int *b = (int *)calloc(range, sizeof(int));
	//ʹ����ʱ�����¼ԭʼ������ÿ�����ĸ���
	for (int i = 0; i < len; i++){
		//ע�⣺�����ڴ洢��Ҫ��ԭʼ������ֵ�ϼ�ȥmin�Ų������Խ������
		b[a[i] - min] += 1;
	}
	int j = 0;
	//����ͳ�ƽ�������¶�Ԫ�ؽ��л���
	for (int i = 0; i < range; i++){
		while (b[i]--){
			//ע�⣺Ҫ��i��ֵ����min���ܻ�ԭ��ԭʼ����
			a[j++] = i + min;
		}
	}
	//�ͷ���ʱ����
	free(b);
	b = NULL;
}

void count_sort(int a[], int n, int exp) {
	int *output = (int *)malloc(n*sizeof(int)); // �洢�����������ݡ�����ʱ����
	int i, buckets[10] = { 0 };
	// �����ݳ��ֵĴ����洢��buckets[]��
	for (i = 0; i < n; i++) {
		buckets[(a[i] / exp) % 10]++;
	}
	// ����buckets[i]��Ŀ�����øĺ��buckets[i]��ֵ���Ǹ�������output[]�е�λ�á�
	for (i = 1; i < 10; i++) {
		buckets[i] += buckets[i - 1];
	}
	// �����ݴ洢����ʱ����output[]��
	for (i = n - 1; i >= 0; i--) {
		output[buckets[(a[i] / exp) % 10] - 1] = a[i];
		buckets[(a[i] / exp) % 10]--;
	}
	// ������õ����ݸ�ֵ��a[]
	for (i = 0; i < n; i++) {
		a[i] = output[i];
	}
}

void radix_sort(int arr[], int n) {//�������� 
    int exp;
	// ָ�����������鰴��λ��������ʱ��exp=1;��ʮλ��������ʱ��exp=10��
	int max = get_max(arr, n);// ����a�е����ֵ
	// �Ӹ�λ��ʼ��������a��ָ����������
	for (exp = 1; max / exp > 0; exp *= 10) {
		count_sort(arr, n, exp);//��Ͱ 
	}
}
int SelectMedianOfThree(int a,int b,int c){
    if ((a-b)*(a-c)<=0)
        return a;
    if ((b-a)*(b-c)<=0)
        return b;
    if ((c-a)*(c-b)<=0)
        return c;
}
//������[L,R]��Hoare˫��ɨ��
int Partitionthree(int arr[],int L,int R){//������
    int pivot=SelectMedianOfThree(arr[L],arr[(L+R)/2],arr[R]);//����ȡ�� 
    int i=L-1,j=R+1;
    while(1){
        do ++i;while(arr[i]<pivot);//����ȡ�Ⱥţ�ȡ�Ⱥſ���Խ��
        do --j;while(arr[j]>pivot);
        if(i>=j)    return j;//j�ұ߶����ڵ���pivot��j���(����j)��С�ڵ���pivot
        swap(arr[i],arr[j]);
    }
}
int Partitionrandom(int arr[],int L,int R){//������
    int pivot=arr[L+rand()%(R-L+1)]; //���ѡ������ 
    int i=L-1,j=R+1;
    while(1){
        do ++i;while(arr[i]<pivot);//����ȡ�Ⱥţ�ȡ�Ⱥſ���Խ��
        do --j;while(arr[j]>pivot);
        if(i>=j)    return j;//j�ұ߶����ڵ���pivot��j���(����j)��С�ڵ���pivot
        swap(arr[i],arr[j]);
    }
}
void quicksort(int arr[],int L,int R){//��������ʹ������ȡ�к���� 
    if(L<R){
	    int index=Partitionrandom(arr,L,R);
        //�Ҷ˵㲻��ѡindex+1,��Ϊarr[index]С�ڵ���pivot�����pivot��Զȡ���ֵ�����������ѭ��
	    quicksort(arr,L,index);
	    quicksort(arr,index+1,R);
	}
}

void color(){
	int n;
	printf("������������Գ���");
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++){
		printf("����������");
		scanf("%d",&a[i]);
	}
	int i=0;
	int high=n-1;
	int low=0;//��ʼ��ָ��λ��
	while(i <= high) {
        if (a[i] == 2) {
            swap(a[i], a[high]);//2�͵���ĩ�� 
            --high;
        } 
		else if (a[i] == 0) {
            swap(a[i], a[low]);//0�͵���ǰ�� 
            ++low;
            ++i;
        } 
		else {
        	++i;
        }
    }
    printf("������Ϊ:");
    for(int i=0;i<n;i++){
    	printf("%d ",a[i]);
	}
	printf("\n");
}
int findKthSmallest(int* a, int start, int end, int k) {
    if (start == end) return a[start];
    int pivot = a[start], i = start - 1, j = end + 1;
    while (i < j) {
        do i++;
        while (a[i] < pivot);
        do j--;
        while (a[j] > pivot);
        if (i < j) {
            swap(a[i],a[j]);
        }
    }
    if (k <= j) return findKthSmallest(a, start, j, k);
    return findKthSmallest(a, j + 1, end, k);
}
void findsmallest(){
	int n;
	printf("���볤��:"); 
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++){
		printf("��������:");
		scanf("%d",&a[i]);
	}
	int k;
	printf("������Ҫ��ѯ��kС��k");
	scanf("%d",&k);
	k=findKthSmallest(a,0,n-1,k-1);
	if(k!=-1){
		printf("��kС������%d\n",k);
	}
	else{
		printf("��ѯ�������鷶Χ��"); 
	}
} 

void generateRandomData(int arr[], int size) {//�����������ĺ��� 
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; ++i) {
        arr[i] = (rand() % 10000) ; // ���� �����
    }
}
void saveDataToFile(int arr[], int size, FILE *file) {
    if (file == NULL) {
        printf("�Ҳ����ļ�");
        return;
    }
	
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%d ", arr[i]);
    }
    fprintf(file, "\\n");
}
void readDataFromFile(int arr[], int size, FILE *file) {
    if (file == NULL) {
        printf("�Ҳ����ļ�");
        return;
    }
    fseek(file,0,SEEK_SET);
    for (int i = 0; i < size; ++i) {
        fscanf(file, "%d", &arr[i]);
    }
}
 
void random(){
	int arr[200000];
	int dataSizes[3] = {10000, 50000, 200000}; // ��ͬ���ȵ�����
    FILE *file = fopen("randomtest", "w");

    for (int i=0;i<3;++i){
        generateRandomData(arr, dataSizes[i]);
        saveDataToFile(arr, dataSizes[i], file);
    }
    for (int i=0;i<100;i++){
    	generateRandomData(arr,10000);
    	saveDataToFile(arr,10000,file);
	}
    fclose(file);
}
void testing(){
	clock_t start,end;
	int arr[200000];
	char name[100];
	printf("������Ҫ��ѯ���ļ����������������ɲ��ԣ�������randomtest\n");
	scanf("%s",name);
	FILE *file = fopen(name,"r");
	if(file==NULL){
		printf("�Ҳ����ļ�");
		return; 
	}
	readDataFromFile(arr,10000,file);
	start=clock();
	insertSort(arr,10000);
	end=clock();
	printf("��������10000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,50000,file);
	start=clock();
	insertSort(arr,50000);
	end=clock();
	printf("��������50000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,200000,file);
	start=clock();
	insertSort(arr,200000);
	end=clock();
	printf("��������200000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	start=clock();
	for(int i=0;i<100;i++){
		readDataFromFile(arr,10000,file);
		insertSort(arr,10000);
	}
	end=clock();
	printf("��������100*10000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,10000,file);
	start=clock();
	merge_sort(arr,0,9999);
	end=clock();
	printf("�鲢����10000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,50000,file);
	start=clock();
	merge_sort(arr,0,49999);
	end=clock();
	printf("�鲢����50000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,200000,file);
	start=clock();
	merge_sort(arr,0,199999);
	end=clock();
	printf("�鲢����200000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	start=clock();
	for(int i=0;i<100;i++){
		readDataFromFile(arr,10000,file);
		merge_sort(arr,0,9999);
	}
	end=clock();
	printf("�鲢����100*10000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,10000,file);
	start=clock();
	quicksort(arr,0,9999);
	end=clock();
	printf("��������10000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,50000,file);
	start=clock();
	quicksort(arr,0,49999);
	end=clock();
	printf("��������50000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,200000,file);
	start=clock();
	quicksort(arr,0,199999);
	end=clock();
	printf("��������200000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	start=clock();
	for(int i=0;i<100;i++){
		readDataFromFile(arr,10000,file);
		quicksort(arr,0,9999);
	}
	end=clock();
	printf("��������100*10000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,10000,file);
	start=clock();
	counting_sort(arr,10000);
	end=clock();
	printf("��������10000ʱ��=%fs\n",(double)(end-start)/CLK_TCK); 
	readDataFromFile(arr,50000,file);
	start=clock();
	counting_sort(arr,50000);
	end=clock();
	printf("��������50000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,200000,file);
	start=clock();
	counting_sort(arr,200000);
	end=clock();
	printf("��������100000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	start=clock();
	for(int i=0;i<100;i++){
		readDataFromFile(arr,10000,file);
		counting_sort(arr,10000);
	} 
	end=clock();
	printf("��������100*10000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,10000,file);
	start=clock();
	radix_sort(arr,10000);
	end=clock();
	printf("��������10000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,50000,file);
	start=clock();
	radix_sort(arr,50000);
	end=clock();
	printf("��������50000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,200000,file);
	start=clock();
	radix_sort(arr,200000);
	end=clock();
	printf("��������200000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
	start=clock();
	for(int i=0;i<100;i++){
		readDataFromFile(arr,10000,file);
		radix_sort(arr,10000);
	}
	end=clock();
	printf("��������100*10000ʱ��=%fs\n",(double)(end-start)/CLK_TCK);
}
	
	

int main(){
	printf("----���������㷨ʵ��-----\n");
	printf("1.���������������ļ�\n");
	printf("2.��ȡ��֪�ļ���������\n");
	printf("3.��ɫ������\n");
	printf("4.012���е�������\n");
	printf("0.�˳�\n");
	printf("������������룺");
	int a;
	do{
		scanf("%d",&a);
		if(a==0)  break;
		else{
			switch(a){
				case 1:
					random(); 
					printf("������������룺");
					break;
				case 2:
					testing();
					printf("������������룺");
					break;
				case 3:
					color();
					printf("������������룺");
					break;
				case 4:
					findsmallest();
					printf("������������룺");
					break;
			}
		}
	}while(a!=0);
}
