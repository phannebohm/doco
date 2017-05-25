#include "Complex.h"
#include <cmath> /* hypot, atan2 */

// lokale Konstanten, die immer wieder auftauchen
static const double PI = 3.14159265358979323846;
static const Complex I(0.0, 1.0);

// Konstruktoren ---------------------------------------------------------------

Complex::Complex(double a, double b)
  : real(a), imag(b)
{}

Complex::Complex(const Complex& z)
  : real(z.real), imag(z.imag)
{}


// Zuweisungsoperatoren --------------------------------------------------------

Complex& Complex::operator=(const Complex& z)
{
  real = z.real;
  imag = z.imag;
  return *this;
}

Complex& Complex::operator+=(const Complex& z)
{
  real += z.real;
  imag += z.imag;
  return *this;
}

Complex& Complex::operator-=(const Complex& z)
{
  real -= z.real;
  imag -= z.imag;
  return *this;
}

Complex& Complex::operator*=(const Complex& z)
{
  double a = real;
  real = real * z.real - imag * z.imag;
  imag = imag * z.real + a * z.imag;
  return *this;
}


// Bei der Division kann Über- oder Unterlauf und allgemein
// Präzisionsverlust vermieden werden, indem durch den
// größeren (Real- bzw. Imgainär-)Teil gekürzt wird.
//
//     (a + bi)   (a + b*d/c) + i*(b - a*d/c)
//     -------- = --------------------------- ,  für |c|>=|d|
//     (c + di)           (c + d*d/c)
//
//     (a + bi)   (a*c/d + b) + i*(b*c/d - a)
//     -------- = --------------------------- ,  für |c|<|d|
//     (c + di)           (c*c/d + d)
Complex& Complex::operator/=(const Complex& z)
{
  double a = real;
  if(fabs(z.real) >= fabs(z.imag)) {
    double dc = z.imag / z.real;
    double denom = 1 / (z.real + z.imag * dc);
    real = (real + imag * dc) * denom;
    imag = (imag - a * dc) * denom;
  } else {
    double cd = z.real / z.imag;
    double denom = 1 / (z.real * cd + z.imag);
    real = (real * cd + imag) * denom;
    imag = (imag * cd - a) * denom;
  }
  return *this;
}


Complex& Complex::operator=(const double x)
{
  real = x;
  imag = 0.0;
  return *this;
}

Complex& Complex::operator+=(const double x)
{
  real += x;
  return *this;
}

Complex& Complex::operator-=(const double x)
{
  real -= x;
  return *this;
}

Complex& Complex::operator*=(const double x)
{
  real *= x;
  imag *= x;
  return *this;
}

Complex& Complex::operator/=(const double x)
{
  real /= x;
  imag /= x;
  return *this;
}


// Arithmetische Operatoren ----------------------------------------------------

Complex Complex::operator-() const
{
  return Complex(-real, -imag);
}


Complex Complex::operator+(const Complex& z) const
{
  return Complex(real + z.real, imag + z.imag);
}

Complex Complex::operator-(const Complex& z) const
{
  return Complex(real - z.real, imag - z.imag);
}

Complex Complex::operator*(const Complex& z) const
{
  return Complex(real * z.real - imag * z.imag, imag * z.real + real * z.imag);
}

Complex Complex::operator/(const Complex& z) const
{
  // gleiches Verfahren wie oben bei operator/=
  if(fabs(z.real) >= fabs(z.imag)) {
    double dc = z.imag / z.real;
    double denom = 1 / (z.real + z.imag * dc);
    return Complex((real + imag * dc) * denom, (imag - real * dc) * denom);
  }
  double cd = z.real / z.imag;
  double denom = 1 / (z.real * cd + z.imag);
  return Complex((real * cd + imag) * denom, (imag * cd - real) * denom);
}


Complex Complex::operator+(const double x) const
{
  return Complex(real + x, imag);
}

Complex Complex::operator-(const double x) const
{
  return Complex(real - x, imag);
}

Complex Complex::operator*(const double x) const
{
  return Complex(real * x, imag * x);
}

Complex Complex::operator/(const double x) const
{
  return Complex(real / x, imag / x);
}


Complex operator+(const double x, const Complex& z)
{
  return Complex(x + z.real, z.imag);
}

Complex operator-(const double x, const Complex& z)
{
  return Complex(x - z.real, -z.imag);
}

Complex operator*(const double x, const Complex& z)
{
  return Complex(x * z.real, x * z.imag);
}

Complex operator/(const double x, const Complex& z)
{
  double denom = x / (z.real * z.real + z.imag * z.imag);
  return Complex(z.real * denom, -z.imag * denom);
}


// Vergleichsoperatoren --------------------------------------------------------

bool Complex::operator==(const Complex& z) const
{
  return real == z.real && imag == z.imag;
}

bool Complex::operator!=(const Complex& z) const
{
  return real != z.real || imag != z.imag;
}

bool Complex::operator==(const double x) const
{
  return real == x && imag == 0.0;
}

bool Complex::operator!=(const double x) const
{
  return real != x || imag != 0.0;
}

bool operator==(const double x, const Complex& z)
{
  return x == z.real && 0.0 == z.imag;
}

bool operator!=(const double x, const Complex& z)
{
  return x != z.real || 0.0 != z.imag;
}


// Mathematische Funktionen ----------------------------------------------------

double Re(const Complex& z)
{
  return z.real;
}

double Im(const Complex& z)
{
  return z.imag;
}

double abs(const Complex& z)
{
  return hypot(z.real, z.imag);
}

double arg(const Complex& z, const int branch)
{
  return atan2(z.imag, z.real) + 2 * PI * branch;
}

Complex conj(const Complex& z)
{
  return Complex(z.real, -z.imag);
}


Complex cos(const Complex& z)
{
  return Complex(cos(z.real) * cosh(z.imag), -sin(z.real) * sinh(z.imag));
}

Complex sin(const Complex& z)
{
  return Complex(sin(z.real) * cosh(z.imag), cos(z.real) * sinh(z.imag));
}

Complex tan(const Complex& z)
{
  return sin(z) / cos(z);
}

Complex acos(const Complex& z, const int branch)
{
  return 0.5 * PI - asin(z, branch);
}

Complex asin(const Complex& z, const int branch)
{
  return -I * ln(I * z + sqrt(1 - z * z, 0), branch);
}

Complex atan(const Complex& z, const int branch)
{
  return 0.5 * I * ln((I + z) / (I - z), branch);
}


Complex cosh(const Complex& z)
{
  return Complex(cos(z.imag) * cosh(z.real), sin(z.imag) * sinh(z.real));
}

Complex sinh(const Complex& z)
{
  return Complex(cos(z.imag) * sinh(z.real), sin(z.imag) * cosh(z.real));
}

Complex tanh(const Complex& z)
{
  return sinh(z) / cosh(z);
}


Complex acosh(const Complex& z, const int branch)
{
  return ln(z + sqrt(z + 1, 0) * sqrt(z - 1, 0), branch);
}

Complex asinh(const Complex& z, const int branch)
{
  return ln(z + sqrt(z * z + 1, 0), branch);
}

Complex atanh(const Complex& z, const int branch)
{
  return 0.5 * ln((1 + z) / (1 - z), branch);
}


Complex exp(const Complex& z)
{
  return Complex(exp(z.real) * cos(z.imag), exp(z.real) * sin(z.imag));
}

Complex ln(const Complex& z, const int branch)
{
  return Complex(log(abs(z)), arg(z, branch));
}

Complex pow(const Complex& z, const Complex& w, const int branch)
{
  return exp(ln(z, branch) * w);
}

Complex sqrt(const Complex& z, const int branch)
{
  return pow(z, 0.5, branch);
}

Complex gamma(const Complex& z)
{
  // Lanczos-Approximation
  // https://en.wikipedia.org/wiki/Lanczos_approximation
  static const double p[9] = {
    +9.9999999999980993e-1,
    +6.7652036812188510e+2,
    -1.2591392167224028e+3,
    +7.7132342877765313e+2,
    -1.7661502916214059e+2,
    +1.2507343278686905e+1,
    -1.3857109526572012e-1,
    +9.9843695780195716e-6,
    +1.5056327351493116e-7
  };

  if(z.real < 0.5) {
    return PI / (sin(PI * z) * gamma(1 - z));
  } else {
    Complex w = z - 1;
    Complex Ag = p[0];

    for(int i = 1; i < 9; ++i) {
      Ag += p[i] / (w + i);
    }
    Complex t = w + 7.5;
    return sqrt(2 * PI) * pow(t, w + 0.5, 0) * exp(-t) * Ag;
  }
}

Complex zeta(const Complex& z)
{
  // Stieltjes-Konstanten
  // http://beta.lmfdb.org/riemann/stieltjes/
  static const double g[200] = {
    +5.77215664901532861e-1,
    +7.28158454836767249e-2,
    -4.84518159643615924e-3,
    -3.42305736717224311e-4,
    +9.68904193944708357e-5,
    -6.61103181084218918e-6,
    -3.31624090875277236e-7,
    +1.04620945844791874e-7,
    -8.73321810027379736e-9,
    +9.47827778276235895e-11,
    +5.65842192760870797e-11,
    -6.76868986351369666e-12,
    +3.49211593667203185e-13,
    +4.41042474175775338e-15,
    -2.39978622177099918e-15,
    +2.16773122007268285e-16,
    -9.54446607636696517e-18,
    -7.38767666053863650e-20,
    +4.80085078248806523e-20,
    -4.13995673771330564e-21,
    +1.91682015939912339e-22,
    -2.04415431222621661e-24,
    -4.81849850110735344e-25,
    +4.81185705151256648e-26,
    -2.56026331031881494e-27,
    +6.92784089530466712e-29,
    +1.62860755048558674e-30,
    -3.19393756115325558e-31,
    +2.09915158936342553e-32,
    -8.33674529544144048e-34,
    +1.34125937721921867e-35,
    +9.13714389129817200e-37,
    -9.76842144689316563e-38,
    +5.19464288745573322e-39,
    -1.73174959516100442e-40,
    +1.97162023326628724e-42,
    +1.94848008275558833e-43,
    -1.71484028164349789e-44,
    +8.20162325795024844e-46,
    -2.53909617003982347e-47,
    +3.04837480681247325e-49,
    +2.15103288078139524e-50,
    -1.87813767783170615e-51,
    +8.71456987091534575e-53,
    -2.70429325494165277e-54,
    +4.24030297482975157e-56,
    +1.20123014394335413e-57,
    -1.31619164554817482e-58,
    +6.33824832920169120e-60,
    -2.06884990450560310e-61,
    +4.16989590352731965e-63,
    +1.23761716066823695e-65,
    -5.74261594742320623e-66,
    +3.13613040471976402e-67,
    -1.11437079290236313e-68,
    +2.72292956701731375e-70,
    -2.89068902735437413e-72,
    -1.32560833116286161e-73,
    +1.02185759026750415e-74,
    -4.14068560753090874e-76,
    +1.18427361147156593e-77,
    -2.20006522637922258e-79,
    +1.69484262549863223e-82,
    +1.97201173966447498e-82,
    -1.02704091751813605e-83,
    +3.44955999389669994e-85,
    -8.34126724395200229e-87,
    +1.19050531494398311e-88,
    +1.15787330336037016e-90,
    -1.55472926954800695e-91,
    +6.62196339469732755e-93,
    -1.95437176527534198e-94,
    +4.16682477597532927e-96,
    -4.75727380025865151e-98,
    -9.03196603126424231e-100,
    +7.73701694196172451e-101,
    -2.92526637876817128e-102,
    +7.90963384750680700e-104,
    -1.55154680471827323e-105,
    +1.56055636403532969e-107,
    +3.51594689261433542e-109,
    -2.60574826714850550e-110,
    +9.21197490310667019e-112,
    -2.36142741505271343e-113,
    +4.44174157374990728e-115,
    -4.46928802307050462e-117,
    -8.08520457656245556e-119,
    +6.14470437811313975e-120,
    -2.11864320045875785e-121,
    +5.30231918757459923e-123,
    -9.90505944201433385e-125,
    +1.09317701976757737e-126,
    +1.04083377155742139e-128,
    -1.02748204048476579e-129,
    +3.60567100875745568e-131,
    -9.04326263697638441e-133,
    +1.72185412741341618e-134,
    -2.15379864461690346e-136,
    -3.02783602415645203e-139,
    +1.20635783028923800e-139,
    -4.55756354361418183e-141,
    +1.17525153256876433e-142,
    -2.32237926975193188e-144,
    +3.28087312507692495e-146,
    -1.54428793555629447e-148,
    -9.41209669193569645e-150,
    +4.24752462379217509e-151,
    -1.16132854807249106e-152,
    +2.41630319602487670e-154,
    -3.80074754244562417e-156,
    +3.43144464590540143e-158,
    +3.81690351184559081e-160,
    -2.84187103420120765e-161,
    +8.65305848867246870e-163,
    -1.92746510268125217e-164,
    +3.33650850725054430e-166,
    -4.04788825930299178e-168,
    +9.61700518843098777e-171,
    +1.25879289308475265e-171,
    -4.76581220971398847e-173,
    +1.16875698815969009e-174,
    -2.21941600647795968e-176,
    +3.22153149864945140e-178,
    -2.74682036737281440e-180,
    -2.51122990563663242e-182,
    +1.84604995486422423e-183,
    -5.30052296472061536e-185,
    +1.11602928202382084e-186,
    -1.84945361526996092e-188,
    +2.24208027805046581e-190,
    -1.02640759265748847e-192,
    -4.25642528959589149e-194,
    +1.73172812435616813e-195,
    -4.19885770767640126e-197,
    +7.84856069399527543e-199,
    -1.15285197984565120e-200,
    +1.15513849448046629e-202,
    +1.59493306121335772e-207,
    -3.64730844284194165e-206,
    +1.14765190244562376e-207,
    -2.46898922313896939e-209,
    +4.18990968023723711e-211,
    -5.53111925176162841e-213,
    +4.53262654146936101e-215,
    +2.46894592412629128e-217,
    -2.08642348311267103e-218,
    +5.63744411118706554e-220,
    -1.10866415860858695e-221,
    +1.73913924128499345e-223,
    -2.09550627235117676e-225,
    +1.40527116551455804e-227,
    +1.61840190486161357e-229,
    -8.65214228379745976e-231,
    +2.11383524708867197e-232,
    -3.88257963400287585e-234,
    +5.72250950341019891e-236,
    -6.41263928109030519e-238,
    +3.62140121755656987e-240,
    +6.17113953492790203e-242,
    -2.70497036381823538e-243,
    +6.17355769157307956e-245,
    -1.07760933196504323e-246,
    +1.51567706703043964e-248,
    -1.61450988216294084e-250,
    +8.22575590960112775e-253,
    +1.62448192634309421e-254,
    -6.52117800637577946e-256,
    +1.42481687772538093e-257,
    -2.39952688127368843e-259,
    +3.26871570226920220e-261,
    -3.38658316792074462e-263,
    +1.71201451978397007e-265,
    +3.09462291022220524e-267,
    -1.22902325332638473e-268,
    +2.62572772237601181e-270,
    -4.32544675566314085e-272,
    +5.78557204774101285e-274,
    -5.95520841218153381e-276,
    +3.24286953191888604e-278,
    +4.27381457205071888e-280,
    -1.82417698614464028e-281,
    +3.89121627827953336e-283,
    -6.35228031093322823e-285,
    +8.44611489636833948e-287,
    -8.78712128197623992e-289,
    +5.38112109540724637e-291,
    +4.05860750091220767e-293,
    -2.13506975337961431e-294,
    +4.65647188092275330e-296,
    -7.63104463443949036e-298,
    +1.01963913694586148e-299,
    -1.08554911877184651e-301,
    +7.53929386680383785e-304,
    +2.03046986370194378e-306,
    -1.95718461618284376e-307,
    +4.50421721454014318e-309,
    -7.51419518416144983e-311,
    +1.01891445839901791e-312,
    -1.11915397629212199e-314,
    +8.72893293970527359e-317,
  };

  if(z.real > 0.5) {
    // Riemanns Funktionalgleichung
    return pow(2 * PI, z, 0) * 0.5 / cos(PI * z * 0.5) / gamma(z) * zeta(1 - z);
  } else {
    // Laurent Reihenentwicklung
    Complex sum = g[200 - 1];
    Complex oldsum;

    for(int i = 200 - 2; i >= 0; --i) {
      oldsum = sum;
      sum = sum * (z - 1) + g[i];

      // Abbruchkriterium
      if(abs(1 - oldsum / sum) < 1e-4) {
        return sum + 1 / (z - 1);
      }
    }
    return sum + 1 / (z - 1);
  }
}

Complex pe(const Complex& z)
{
  const Complex w2(-0.5, 0.8660254037844386); // = -1/2 +i*sqrt(3)/2
  const Complex w1(1.0, 0.0);
  double d = Im(conj(w1) * w2); // = det(w1|w2)

  if(0.0 == d) {
    // 0 = det(w1|w2) -> w1 und w2 sind linear abhängig...
    return w1;
  }

  // Weierstrass' elliptische Funktion ist doppelt periodisch
  //     pe(z + w1) = Pe(z + w2) = pe(z)
  // also finden wir ganze Zahlen alpha und beta, so dass
  //     z = (alpha+epsilon)*w1  + (beta+delta)*w2
  // mit epsilon, delta aus (-0.5; 0.5)
  double alpha = round(Im(conj(z) * w2) / d);
  double beta  = round(Im(conj(w1) * z) / d);

  // zz := epsilon*w1  + delta*w2
  // damit liegt zz innerhalb eines Parallelogramms um den Ursprung
  Complex zz = z - alpha * w1 - beta * w2;

  Complex sum = 1 / (zz * zz);
  Complex oldsum;  // vorherige Summe
  Complex w;  // Punkt im Gitter von w1, w2

  // durchquere alle Punkte im Gitter von innen nach außen in einer Spirale

  // n=1    |          n=2    |          n=3    0
  //        |                 0               1 x 2
  //        0               1 x 1           2 x x x 1
  // -----0-|-0-----   ---0-x-|-x-0---   -0-x-x-|-x-x-0-
  //        0               1 x 1           1 x x x 2
  //        |                 0               2 x 1
  //        |                 |                 0       ...etc.

  for(int n = 1; n < 10; ++n) {
    oldsum = sum;
    for(int i = 0; i < n; ++i) {
      // 1. Quadrant
      w = (n - i) * w1 + (i) * w2;
      sum += 1 / ((zz - w) * (zz - w)) - 1 / (w * w);
      // 2. Quadrant
      w = (-i) * w1 + (n - i) * w2;
      sum += 1 / ((zz - w) * (zz - w)) - 1 / (w * w);
      // 3. Quadrant
      w = (i - n) * w1 + (-i) * w2;
      sum += 1 / ((zz - w) * (zz - w)) - 1 / (w * w);
      // 4. Quadrant
      w = (i) * w1 + (i - n) * w2;
      sum += 1 / ((zz - w) * (zz - w)) - 1 / (w * w);
    }
    // Abbruchkriterium
    if(abs(1 - oldsum / sum) < 1e-4) {
      return sum;
    }
  }
  return sum;
}


// I/O-Operatoren --------------------------------------------------------------

std::ostream& operator<<(std::ostream& str, const Complex& z)
{
  // visuell optimierte Ausgabe
  if(z.imag == 0) {
    if(z.real < 0) {
      str << "(" << z.real << ")";
    } else {
      str << z.real;
    }
  } else if(z.real == 0) {
    if(z.imag < 0) {
      if(z.imag == -1) {
        str << "(-i)";
      } else {
        str << "(" << z.imag << "i)";
      }
    } else {
      if(z.imag == 1) {
        str << "i";
      } else {
        str << z.imag << "i";
      }
    }
  } else {
    str << "(" << z.real;
    if(z.imag > 0) {
      str << "+";
      if(z.imag != 1) {
        str << z.imag;
      }
    } else {
      if(z.imag != -1) {
        str << z.imag;
      } else {
        str << "-";
      }
    }
    str << "i)";
  }
  return str;
}

std::istream& operator>>(std::istream& str, Complex& z)
{
  char c;
  str >> c;
  if(c != '(') {
    throw "Einlesen komplexer Zahl: Es wurde '(' erwartet";
  }
  str >> z.real;
  str >> c;
  if(c != ',') {
    throw "Einlesen komplexer Zahl: Es wurde ',' erwartet";
  }
  str >> z.imag;
  str >> c;
  if(c != ')') {
    throw "Einlesen komplexer Zahl: Es wurde ')' erwartet";
  }
  return str;
}
