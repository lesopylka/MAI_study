#include <bits/stdc++.h>
using namespace std;

typedef complex<double> cd;

vector<cd> fft(vector<cd>& a)
{
	int n = a.size();
	if (n == 1)
		return vector<cd>(1, a[0]);

	vector<cd> w(n);
	for (int i = 0; i < n; i++) {
		double alpha = -2 * M_PI * i / n;
		w[i] = cd(cos(alpha), sin(alpha));
	}

	vector<cd> A0(n / 2), A1(n / 2);
	for (int i = 0; i < n / 2; i++) {
		A0[i] = a[i * 2];
		A1[i] = a[i * 2 + 1];
	}

	vector<cd> y0 = fft(A0);
	vector<cd> y1 = fft(A1);

	vector<cd> y(n);

	for (int k = 0; k < n / 2; k++) {
		y[k] = y0[k] + w[k] * y1[k];
		y[k + n / 2] = y0[k] - w[k] * y1[k];
	}
	return y;
}

vector<cd> ifft(vector<cd>& y)
{
	y = fft(y);
	for(int i = 0; i < y.size(); ++i){
		y[i] /= y.size();
	}
	vector<cd> a;
	a.push_back(y[0].real());
	for(int i = y.size() - 1; i >= 1; --i){
		a.push_back(y[i].real());
	}
	return a;
}

vector<cd> multiply(vector<cd> a, vector<cd> b){
	size_t n = 1;
	while(n < max(a.size(), b.size()))
		n <<= 1;
	a.resize(n), b.resize(n);
	vector<cd> ya = fft(a);
	vector<cd> yb = fft(b);
	vector<cd> res(n);
	for(int i = 0; i < n; i++){
		res[i] = ya[i] * yb[i];
	}
	res = ifft(res);
	// нужно убрать незначащие нули
	// потом сделать пернос разрядов и всё будет тип топ
	return res;
}

vector<cd> string_to_polinom(string& str){
	vector<cd> res;
	for(int i = str.length() - 1; i >= 0; i--){
		if(isdigit(str[i]))
			res.push_back(str[i] - '0');
	}
	return res;
}

string polinom_to_string(vector<cd> poli){
	string res;
	for(int i = poli.size() - 1; i >= 0; i--){
		res.push_back(poli[i].real() + '0');
	}
	return res;
}

int main()
{
	string in_big_num;
	cin >> in_big_num;
	vector<cd> a = string_to_polinom(in_big_num);
	cin >> in_big_num;
	vector<cd> b = string_to_polinom(in_big_num);
	vector<cd> res = multiply(a, b);
	
	for(int i = 0; i < a.size() + b.size() - 1; i++){
		cout << res[i] << endl;
	}
	return 0;
}