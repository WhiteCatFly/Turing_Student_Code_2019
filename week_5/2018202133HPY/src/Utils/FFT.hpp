#include <algorithm>
#include <cmath>
#include <complex>
#include <vector>

namespace cowr {

namespace FFT {

    template <typename Complex = std::complex<double>>
    void build(std::vector<Complex>& _P, std::vector<Complex>& P, int n, int m, int curr, int& cnt)
    {
        if (m == n)
            _P[curr] = P[cnt++];
        else
            build(_P, P, n, m * 2, curr, cnt),
                build(_P, P, n, m * 2, curr + m, cnt);
    }

    template <typename Complex = std::complex<double>>
    void FFT(std::vector<Complex>& P, int n, int oper = 1)
    {
        const static long double pi = acosl(-1);

        static std::vector<Complex> _P;

        _P.resize(n);

        int cnt = 0;
        build(_P, P, n, 1, 0, cnt);
        copy(_P.begin(), _P.end(), P.begin());
        for (int d = 0; (1 << d) < n; d++) {
            int m = 1 << d;
            int m2 = m << 1;
            double p0 = pi / m * oper;
            Complex unit_p0 = Complex(cos(p0), sin(p0));
            for (int i = 0; i < n; i += m2) {
                Complex unit = 1;
                for (int j = 0; j < m; j++) {
                    Complex &P1 = P[i + j + m], &P2 = P[i + j];
                    Complex t = unit * P1;
                    P1 = P2 - t;
                    P2 = P2 + t;
                    unit = unit * unit_p0;
                }
            }
        }
    }

    template <typename Complex = std::complex<double>>
    void iFFT(std::vector<Complex>& P, int n)
    {
        FFT(P, n, -1);
        for (int i = 0; i <= n; i++)
            P[i] /= n;
    }
}
}
