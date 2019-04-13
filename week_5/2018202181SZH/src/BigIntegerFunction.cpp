#include"BigInteger.h"
void strcpy_(char des[],char src[]){
	int len = strlen(src);
	for(int i = 0;i < len;i++){
		des[i] = src[len - i - 1];
	}
	des[len] = '\0';
	return;
}
void caculate(int max,int min,char big[],char small[],char sum[]){
	int sum_ = 0;
	for(int i = 0;i <= max;i++){
		if(i == max ){
			if(sum_) {
				sum[i] = sum_ + '0';
				sum[i+1] = '\0';
				break;
			}
			else {
				sum[i] = '\0';
				break;
			}
		}
        if(i < min){
			sum[i] = '0'; 
			int num_1 = big[i] - '0';
			int num_2 = small[i] - '0';
			sum_ += num_1 + num_2;
			sum[i] = sum[i] + sum_ % 10;
		}else{
			if(sum_){
				sum_ = sum_ + big[i] - '0';
				sum[i] = sum[i] + sum_ % 10;
			} 
			else sum[i] = big[i];
		}
		sum_ = sum_ / 10;
	}
	//cout<<"max: "<<max<<"min: "<<min<<"real len: "<<strlen(sum)<<endl;
	//cout<<sum<<endl;
}
BigInteger operator+(const BigInteger & num1,const BigInteger & num2){
    char* aa = new char(num1.len + 1);
    char* bb = new char(num2.len + 1);
    num1.number.copy(aa,num1.len,0);
    num2.number.copy(bb,num2.len,0);
	int max,min;
	if(strlen(aa)>strlen(bb)) {
		max = strlen(aa);
		min = strlen(bb);
	} 
	else {
		max = strlen(bb);
		min = strlen(aa);
	}
	char big[max + 1],small[max + 1];
	if(strlen(aa)>strlen(bb)) {
		strcpy_(big,aa);
		strcpy_(small,bb);
	} 
	else {
		strcpy_(big,bb);
		strcpy_(small,aa);
	}
    char sum[max + 1];
	for(int i = 0;i < max + 1;i++)sum[i] = '0';
	caculate(max,min,big,small,sum);
    char sum__[max + 2];
    strcpy_(sum__,sum);
	//cout<<sum__<<endl;
    string res = sum__;
    BigInteger result(res);
	delete []aa;
	delete []bb;
    return result;
}
BigInteger operator+(const BigInteger & num1,long long int&num_2){
	char* aa = new char(num1.len + 1);
	string num2 = std::to_string(num_2);
	char* bb = new char(num2.length() + 1);
	num1.number.copy(aa,num1.len,0);
	num2.copy(bb,num2.length(),0);
	int max,min;
	if(strlen(aa)>strlen(bb)) {
		max = strlen(aa);
		min = strlen(bb);
	} 
	else {
		max = strlen(bb);
		min = strlen(aa);
	}
	char big[max + 1],small[max + 1];
	if(strlen(aa)>strlen(bb)) {
		strcpy_(big,aa);
		strcpy_(small,bb);
	} 
	else {
		strcpy_(big,bb);
		strcpy_(small,aa);
	}
    char sum[max + 1];
	for(int i = 0;i < max + 1;i++)sum[i] = '0';
	caculate(max,min,big,small,sum);
    char sum__[max + 2];
    strcpy_(sum__,sum);
	//cout<<sum__<<endl;
    string res = sum__;
    BigInteger result(res);
	delete []aa;
	delete []bb;
    return result;
}
ostream& operator<<(ostream& os,const BigInteger &t){
	 	os<<"a big integer: "<<t.number;
        return os;
}