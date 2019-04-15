#include "bigint.h"

BigInteger::BigInteger () {
	sign = false;
	len = init_len;
	x [len] = 0;
}

BigInteger::BigInteger (const std::string & s) {
	if (s == "") {
		sign = false;
		len = init_len;
		x [len] = 0;
		return;
	}
	int pl = 0, pr = s.size () - 1;
	if (s[pl] == '-') {
		sign = true;
		pl++;
	}
	else {
		sign = false;
	}
	len = 0;
	while (pl <= pr) {
		len++;
		x[len] = s[pr] - ascii0;
		pr--;
	}
}

/*BigInteger::BigInteger (const int & v) {
	if (v == 0) {
		BigInteger ();
		return;
	}
	int v_ = v;
	if (v_ < 0) {
		sign = true;
		v_ = -v_;
	}
	else {
		sign = false;
	}
	len = 0;
	while (v_) {
		len++;
		x[len] = v_ % decimal;
		v_ /= decimal;
	}
}*/

BigInteger::BigInteger (const ll & v) {
	if (v == 0) {
		sign = false;
		len = init_len;
		x [len] = 0;
		return;
	}
	ll v_ = v;
	if (v_ < 0) {
		sign = true;
		v_ = -v_;
	}
	else {
		sign = false;
	}
	len = 0;
	while (v_) {
		len++;
		x[len] = v_ % decimal;
		v_ /= decimal;
	}
}

BigInteger::BigInteger (const BigInteger & rhs) {
	sign = rhs.sign;
	len = rhs.len;
	for (int i = 1; i <= rhs.len; i++) {
		x[i] = rhs.x[i];
	}
}

bool BigInteger::operator < (const BigInteger & rhs) const {
	if (len < rhs.len) {
		return true;
	}
	if (len > rhs.len) {
		return false;
	}
	for (int i = len; i > 0; i--) {
		if (x[i] < rhs.x[i]) {
			return true;
		}
		if (x[i] > rhs.x[i]) {
			return false;
		}
	}
	return false;
}

bool BigInteger::operator > (const BigInteger & rhs) const {
	return rhs < (*this);
}

BigInteger BigInteger::operator - () const {
	BigInteger t = (*this);
	t.sign = !sign;
	return t;
}

BigInteger BigInteger::operator + (const BigInteger & rhs) const {
	BigInteger t;
	if (sign == rhs.sign) {
		t.sign = sign;
		t.len = std::max (len, rhs.len);
		int res = 0;
		for (int i = 1; i <= t.len; i++) {
			t.x[i] = (i<=len?x[i]:0) + (i<=rhs.len?rhs.x[i]:0) + res;
			if (t.x[i] >= decimal) {
				t.x[i] -= decimal;
				res = 1;
			}
			else {
				res = 0;
			}
			if ((i == t.len) && (res > 0)) {
				t.len++;
				t.x[t.len] = 0;
			}
		}
		return t;
	}
	else {
		if ((*this) < rhs) {
			return rhs + (*this);
		}
		if ((*this) > rhs) {
			t.sign = sign;
			t.len = len;
			int res = 0;
			for (int i = 1; i <= t.len; i++) {
				t.x[i] = x[i] - (i<=rhs.len?rhs.x[i]:0) + res;
				if (t.x[i] < 0) {
					res = -1;
					t.x[i] += decimal;
				}
				else {
					res = 0;
				}
			}
			while (t.x[t.len] == 0) {
				t.len--;
			}
		}
		return t;
	}
}

BigInteger operator + (const BigInteger &t, ll v) {
	BigInteger t2(v);
	return t + t2;
}

BigInteger operator + ( ll v, const BigInteger & t) {
	BigInteger t2(v);
	return t + t2;
}

BigInteger BigInteger::operator - (const BigInteger & rhs) const {
	return (*this) + (-rhs);
}

BigInteger BigInteger::operator * (const BigInteger & rhs) const {
	BigInteger t;
	t.sign = sign ^ rhs.sign;
	t.len = len + rhs.len - 1;
	for (int i = 1; i <= t.len; i++) {
		t.x[i] = 0;
		for (int j = 1; j <= i; j++) {
			int k = i - j + 1;
			if (j <= len && k <= rhs.len) {
				t.x[i] += x[j] * rhs.x[k];
			}
		}
	}
	int res = 0;
	for (int i = 1; i <= t.len; i++) {
		t.x[i] += res;
		if (t.x[i] >= decimal) {
			res = t.x[i] / decimal;
			t.x[i] %= decimal;
		}
		else {
			res = 0;
		}
		if ((i == t.len) && (res > 0)) {
			t.len++;
			t.x[t.len]=0;
		}
	}
	return t;
}

BigInteger operator * (const BigInteger & t, ll v) {
	BigInteger t2(v);
	return t * t2;
}

BigInteger operator * (ll v, const BigInteger & t) {
	BigInteger t2(v);
	return t * t2;
}

BigInteger BigInteger::move (int w) const {
	BigInteger t = (*this);
	t.len += w;
	for (int i = t.len; i > w; i--) {
		t.x[i] = t.x[i-w];
	}
	for (int i = w; i > 0; i--) {
		t.x[i] = 0;
	}
	return t;
}

BigInteger BigInteger::operator / (const BigInteger & rhs) const {
	BigInteger t, tmp, last;
	if ((*this) < rhs) {
		return t;
	}
	last = (*this);
	t.sign = sign ^ rhs.sign;
	last.sign = false;
	t.len = len - rhs.len + 1;
	for (int i = t.len; i > 0; i--) {
		t.x[i] = 0;
		tmp = rhs.move (i - 1);
		tmp.sign = false;
		while ((last < tmp) == false) {
			t.x[i]++;
			last = (last - tmp);
		}
	}
	if (t.x[t.len] == 0) {
		t.len--;
	}
	if ((t.sign == true) && (t > BigInteger (0))) {
		t = t - BigInteger (1);
	}
	return t;
}

BigInteger BigInteger::operator %(const BigInteger & rhs) const {
	return (*this) - ((*this) / rhs * rhs);
}

std::ostream & operator << (std::ostream & os, const BigInteger & t) {
	if (t.sign == true)
		os << "-";
	for (int i = t.len; i > 0; i--)
		os << t.x[i];
	return os;
}
