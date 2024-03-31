#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

#include<assert.h>
#define swap(x,y) x=x+y,y=x-y,x=x-y//这里宏定义了交换函数后面方便用了
#define RADIX 10 //基数计数排序专用 
using namespace std;
void BubbleSortflag(int arr[], int n){//冒泡排序（使用标记判断是否已经排好实现剪枝） 
	bool bExchange = false; // 交换标志

	for (int i = 0; i < n - 1; i++) // 最多做n-1趟排序 
	{
		bExchange = false;
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j + 1], arr[j]);
				bExchange = true; // 发生了交换，故将交换标志置为真
			}
		}

		if (!bExchange) // 考虑有一趟排序未发生交换的理想情况，可以提前终止算法
			return;
	}
}
void BubbleSortlast(int arr[], int n){//冒泡排序（在标记优化基础上，记录最后一次交换位置，实现快速定位优化） 
	int i = 0;
	int flag = 0;
	int pos = 0;//用来记录最后一次交换的位置
	int k = n - 1;
	for (i = 0; i < n - 1; i++)//确定排序趟数
	{
		pos = 0;
		int j = 0;
		flag = 0;
		for (j = 0; j < k; j++)//确定比较次数
		{
			if (arr[j]>arr[j + 1])
			{
				//交换
				swap(arr[j],arr[j+1]);
				flag = 1;//加入标记
				pos = j;//交换元素，记录最后一次交换的位置
			}
		}
		if (flag == 0)//如果没有交换过元素，则已经有序
		{
			return;
		}
		k = pos;//下一次比较到记录位置即可
	}
}
void BubbleSortdouble(int arr[], int len){//冒泡排序（在前两项优化基础上，加上双向冒泡优化）

	int i = 0;
	int j = 0;
	int n = 0;//同时找最大值的最小需要两个下标遍历
	int flag = 0;
	int pos = 0;//用来记录最后一次交换的位置
	int k = len - 1;
	for (i = 0; i < len - 1; i++)//确定排序趟数
	{
		pos = 0;
		flag = 0;
		//正向寻找最大值
		for (j = n; j < k; j++)//确定比较次数
		{
			if (arr[j]>arr[j + 1])
			{
				//交换
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = 1;//加入标记
				pos = j;//交换元素，记录最后一次交换的位置
			}
		}
		if (flag == 0)//如果没有交换过元素，则已经有序,直接结束
		{
			return;
		}
		k = pos;//下一次比较到记录位置即可
		//反向寻找最小值
		for (j = k; j > n; j--)
		{
			int tmp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = tmp;
			flag = 1;
		}
		n++;
		if (flag == 0)//如果没有交换过元素，则已经有序,直接结束
		{
			return;
		}
	}
}
void insertSort(int arr[], int n) {//插入排序 
	int i, j, temp;
	for (i = 1; i < n; i++) {
		temp = arr[i];

		for (j = i; j > 0 && arr[j - 1] > temp; j--)
			arr[j] = arr[j - 1]; // 把已排序元素逐步向后挪位

		arr[j] = temp; // 插入
	}
}
void merge(int arr[], int L, int M, int R) { 
    int LEFT_SIZE = M - L + 1;
    int RIGHT_SIZE = R - M;
    int left[LEFT_SIZE];
    int right[RIGHT_SIZE];
    int i, j, k;
    // 以 M 为分割线，把原数组分成左右子数组
    for (i = L; i <= M; i++) left[i - L] = arr[i];
    for (i = M + 1; i <= R; i++) right[i - M - 1] = arr[i];
    // 再合并成一个有序数组（从两个序列中选出最小值依次插入）
    i = 0; j = 0; k = L;
    while (i < LEFT_SIZE && j < RIGHT_SIZE) arr[k++] = left[i] < right[j] ? left[i++] : right[j++];
    while (i < LEFT_SIZE) arr[k++] = left[i++];
    while (j < RIGHT_SIZE) arr[k++] = right[j++];
}

void merge_sort(int arr[], int L, int R) {//归并排序
    if (L == R) return;
    // 将 arr[L..R] 平分为 arr[L..M] 和 arr[M+1..R]
    int M = (L + R) / 2;
    // 分别递归地将子序列排序为有序数列
    merge_sort(arr, L, M);
    merge_sort(arr, M + 1, R);
    // 将两个排序后的子序列再归并到 arr
    merge(arr, L, M, R);
}
void quickSort(int arr[], int begin, int end){
//快速排序未优化 

	int i, j, t, pivot;
	if (begin > end) // 递归，直到start = end为止
		return;

	pivot = arr[begin]; // 基准数
	i = begin;
	j = end;
	while (i != j)
	{
		// 从右向左找比基准数小的数 （要先从右边开始找）
		while (arr[j] >= pivot && i < j)
			j--;
		// 从左向右找比基准数大的数
		while (arr[i] <= pivot && i < j)
			i++;
		if (i < j)
		{
			// 交换两个数在数组中的位置
			t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
		}
	}

	// 最终将基准数归位
	arr[begin] = arr[i];
	arr[i] = pivot;
	quickSort(arr, begin, i - 1); // 继续处理左边的，这里是一个递归的过程
	quickSort(arr, i + 1, end); // 继续处理右边的 ，这里是一个递归的过程
}
int get_max(int a[], int n) {
	int i, max;
	max = a[0];
	for (i = 1; i < n; i++) {
		if (a[i] > max) {
			max = a[i];
		}
	}
	return max;//获取最大值函数 
}
void counting_sort(int a[], int len) {//计数排序 
	//通过max和min计算出临时数组所需要开辟的空间大小
	int max = a[0], min = a[0];
	for (int i = 0; i < len; i++){
		if (a[i] > max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}
	//使用calloc将数组都初始化为0
	int range = max - min + 1;
	int *b = (int *)calloc(range, sizeof(int));
	//使用临时数组记录原始数组中每个数的个数
	for (int i = 0; i < len; i++){
		//注意：这里在存储上要在原始数组数值上减去min才不会出现越界问题
		b[a[i] - min] += 1;
	}
	int j = 0;
	//根据统计结果，重新对元素进行回收
	for (int i = 0; i < range; i++){
		while (b[i]--){
			//注意：要将i的值加上min才能还原到原始数据
			a[j++] = i + min;
		}
	}
	//释放临时数组
	free(b);
	b = NULL;
}

void count_sort(int a[], int n, int exp) {
	int *output = (int *)malloc(n*sizeof(int)); // 存储“被排序数据”的临时数组
	int i, buckets[10] = { 0 };
	// 将数据出现的次数存储在buckets[]中
	for (i = 0; i < n; i++) {
		buckets[(a[i] / exp) % 10]++;
	}
	// 更改buckets[i]。目的是让改后的buckets[i]的值，是该数据在output[]中的位置。
	for (i = 1; i < 10; i++) {
		buckets[i] += buckets[i - 1];
	}
	// 将数据存储到临时数组output[]中
	for (i = n - 1; i >= 0; i--) {
		output[buckets[(a[i] / exp) % 10] - 1] = a[i];
		buckets[(a[i] / exp) % 10]--;
	}
	// 将排序好的数据赋值给a[]
	for (i = 0; i < n; i++) {
		a[i] = output[i];
	}
}

void radix_sort(int arr[], int n) {//基数排序 
    int exp;
	// 指数。当对数组按各位进行排序时，exp=1;按十位进行排序时，exp=10。
	int max = get_max(arr, n);// 数组a中的最大值
	// 从个位开始，对数组a按指数进行排序
	for (exp = 1; max / exp > 0; exp *= 10) {
		count_sort(arr, n, exp);//分桶 
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
//闭区间[L,R]，Hoare双向扫描
int Partitionthree(int arr[],int L,int R){//传引用
    int pivot=SelectMedianOfThree(arr[L],arr[(L+R)/2],arr[R]);//三数取中 
    int i=L-1,j=R+1;
    while(1){
        do ++i;while(arr[i]<pivot);//不能取等号，取等号可能越界
        do --j;while(arr[j]>pivot);
        if(i>=j)    return j;//j右边都大于等于pivot，j左边(包括j)都小于等于pivot
        swap(arr[i],arr[j]);
    }
}
int Partitionrandom(int arr[],int L,int R){//传引用
    int pivot=arr[L+rand()%(R-L+1)]; //随机选择中枢 
    int i=L-1,j=R+1;
    while(1){
        do ++i;while(arr[i]<pivot);//不能取等号，取等号可能越界
        do --j;while(arr[j]>pivot);
        if(i>=j)    return j;//j右边都大于等于pivot，j左边(包括j)都小于等于pivot
        swap(arr[i],arr[j]);
    }
}
void quicksort(int arr[],int L,int R){//快速排序，使用三数取中和随机 
    if(L<R){
	    int index=Partitionrandom(arr,L,R);
        //右端点不能选index+1,因为arr[index]小于等于pivot，如果pivot永远取最大值，则会陷入死循环
	    quicksort(arr,L,index);
	    quicksort(arr,index+1,R);
	}
}

void color(){
	int n;
	printf("请输入数组测试长度");
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++){
		printf("请输入数字");
		scanf("%d",&a[i]);
	}
	int i=0;
	int high=n-1;
	int low=0;//初始化指针位置
	while(i <= high) {
        if (a[i] == 2) {
            swap(a[i], a[high]);//2就掉到末端 
            --high;
        } 
		else if (a[i] == 0) {
            swap(a[i], a[low]);//0就掉到前端 
            ++low;
            ++i;
        } 
		else {
        	++i;
        }
    }
    printf("处理结果为:");
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
	printf("输入长度:"); 
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++){
		printf("输入数字:");
		scanf("%d",&a[i]);
	}
	int k;
	printf("请输入要查询第k小的k");
	scanf("%d",&k);
	k=findKthSmallest(a,0,n-1,k-1);
	if(k!=-1){
		printf("第k小的数是%d\n",k);
	}
	else{
		printf("查询不在数组范围内"); 
	}
} 

void generateRandomData(int arr[], int size) {//生成随机数组的函数 
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; ++i) {
        arr[i] = (rand() % 10000) ; // 生成 随机数
    }
}
void saveDataToFile(int arr[], int size, FILE *file) {
    if (file == NULL) {
        printf("找不到文件");
        return;
    }
	
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%d ", arr[i]);
    }
    fprintf(file, "\\n");
}
void readDataFromFile(int arr[], int size, FILE *file) {
    if (file == NULL) {
        printf("找不到文件");
        return;
    }
    fseek(file,0,SEEK_SET);
    for (int i = 0; i < size; ++i) {
        fscanf(file, "%d", &arr[i]);
    }
}
 
void random(){
	int arr[200000];
	int dataSizes[3] = {10000, 50000, 200000}; // 不同长度的数组
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
	printf("请输入要查询的文件名，如果是随机生成测试，请输入randomtest\n");
	scanf("%s",name);
	FILE *file = fopen(name,"r");
	if(file==NULL){
		printf("找不到文件");
		return; 
	}
	readDataFromFile(arr,10000,file);
	start=clock();
	insertSort(arr,10000);
	end=clock();
	printf("插入排序10000时间=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,50000,file);
	start=clock();
	insertSort(arr,50000);
	end=clock();
	printf("插入排序50000时间=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,200000,file);
	start=clock();
	insertSort(arr,200000);
	end=clock();
	printf("插入排序200000时间=%fs\n",(double)(end-start)/CLK_TCK);
	start=clock();
	for(int i=0;i<100;i++){
		readDataFromFile(arr,10000,file);
		insertSort(arr,10000);
	}
	end=clock();
	printf("插入排序100*10000时间=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,10000,file);
	start=clock();
	merge_sort(arr,0,9999);
	end=clock();
	printf("归并排序10000时间=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,50000,file);
	start=clock();
	merge_sort(arr,0,49999);
	end=clock();
	printf("归并排序50000时间=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,200000,file);
	start=clock();
	merge_sort(arr,0,199999);
	end=clock();
	printf("归并排序200000时间=%fs\n",(double)(end-start)/CLK_TCK);
	start=clock();
	for(int i=0;i<100;i++){
		readDataFromFile(arr,10000,file);
		merge_sort(arr,0,9999);
	}
	end=clock();
	printf("归并排序100*10000时间=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,10000,file);
	start=clock();
	quicksort(arr,0,9999);
	end=clock();
	printf("快速排序10000时间=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,50000,file);
	start=clock();
	quicksort(arr,0,49999);
	end=clock();
	printf("快速排序50000时间=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,200000,file);
	start=clock();
	quicksort(arr,0,199999);
	end=clock();
	printf("快速排序200000时间=%fs\n",(double)(end-start)/CLK_TCK);
	start=clock();
	for(int i=0;i<100;i++){
		readDataFromFile(arr,10000,file);
		quicksort(arr,0,9999);
	}
	end=clock();
	printf("快速排序100*10000时间=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,10000,file);
	start=clock();
	counting_sort(arr,10000);
	end=clock();
	printf("计数排序10000时间=%fs\n",(double)(end-start)/CLK_TCK); 
	readDataFromFile(arr,50000,file);
	start=clock();
	counting_sort(arr,50000);
	end=clock();
	printf("计数排序50000时间=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,200000,file);
	start=clock();
	counting_sort(arr,200000);
	end=clock();
	printf("计数排序100000时间=%fs\n",(double)(end-start)/CLK_TCK);
	start=clock();
	for(int i=0;i<100;i++){
		readDataFromFile(arr,10000,file);
		counting_sort(arr,10000);
	} 
	end=clock();
	printf("计数排序100*10000时间=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,10000,file);
	start=clock();
	radix_sort(arr,10000);
	end=clock();
	printf("基数排序10000时间=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,50000,file);
	start=clock();
	radix_sort(arr,50000);
	end=clock();
	printf("基数排序50000时间=%fs\n",(double)(end-start)/CLK_TCK);
	readDataFromFile(arr,200000,file);
	start=clock();
	radix_sort(arr,200000);
	end=clock();
	printf("基数排序200000时间=%fs\n",(double)(end-start)/CLK_TCK);
	start=clock();
	for(int i=0;i<100;i++){
		readDataFromFile(arr,10000,file);
		radix_sort(arr,10000);
	}
	end=clock();
	printf("基数排序100*10000时间=%fs\n",(double)(end-start)/CLK_TCK);
}
	
	

int main(){
	printf("----各类排序算法实验-----\n");
	printf("1.生成随机数组存入文件\n");
	printf("2.读取已知文件进行排序\n");
	printf("3.颜色排序解决\n");
	printf("4.012数列的排序解决\n");
	printf("0.退出\n");
	printf("请输入操作代码：");
	int a;
	do{
		scanf("%d",&a);
		if(a==0)  break;
		else{
			switch(a){
				case 1:
					random(); 
					printf("请输入操作代码：");
					break;
				case 2:
					testing();
					printf("请输入操作代码：");
					break;
				case 3:
					color();
					printf("请输入操作代码：");
					break;
				case 4:
					findsmallest();
					printf("请输入操作代码：");
					break;
			}
		}
	}while(a!=0);
}
