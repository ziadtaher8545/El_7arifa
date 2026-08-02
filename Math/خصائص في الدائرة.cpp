#include <iostream>
#include <cmath>
using namespace std;

// دالة بتحدد نوع تقاطع دائرتين (من الداخل، من الخارج، أو حالات خاصة)
string intersectType(double x1, double y1, double r1,
    double x2, double y2, double r2) {

    // نحسب فرق الإحداثيات بين المركزين
    double dx = x1 - x2;
    double dy = y1 - y2;

    // نحسب المسافة بين مركزي الدائرتين
    double d = sqrt(dx * dx + dy * dy);

    // مجموع وأنصاف الأقطار
    double sum = r1 + r2;
    double diff = abs(r1 - r2);

    // نفس المركز ونفس نصف القطر → نفس الدائرة
    if (d == 0 && r1 == r2)
        return "Identical";

    // المسافة أكبر من مجموع أنصاف الأقطار → لا يوجد تقاطع
    if (d > sum)
        return "No Intersection";

    // المسافة تساوي مجموع الأنصاف → مماس خارجي
    if (d == sum)
        return "Touching from Outside";

    // المسافة تساوي الفرق → مماس داخلي
    if (d == diff && d != 0)
        return "Touching from Inside";

    // واحدة داخل الثانية بدون تلامس → لا يوجد تقاطع
    if (d < diff)
        return "One inside another (no intersection)";

    // لو وصلنا هنا، يبقى في تقاطع في نقطتين
    // نحدد هل التقاطع من الداخل أو من الخارج حسب المسافة
    if (d > max(r1, r2))
        return "Intersecting from Outside"; // تقاطع من الخارج
    else
        return "Intersecting from Inside";  // تقاطع من الداخل
}

int main() {
    // مثال: دائرتين متقاطعتين
    double x1 = 0, y1 = 0, r1 = 5;
    double x2 = 3, y2 = 0, r2 = 3;

    // نطبع نوع التقاطع
    cout << intersectType(x1, y1, r1, x2, y2, r2) << endl;

    return 0;
}
#include <iostream>
#include <cmath>
using namespace std;

const double pi = 3.141592653589793;

// دالة لحساب المسافة بين مركزين
double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// دالة لحساب مساحة الجزء المتقاطع بين دائرتين
double intersectionArea(double x1, double y1, double r1,
    double x2, double y2, double r2) {
    double d = distance(x1, y1, x2, y2);

    // لا يوجد تقاطع
    if (d >= r1 + r2) return 0;

    // إحدى الدائرتين داخل الأخرى بالكامل
    if (d <= abs(r1 - r2)) {
        double r_min = min(r1, r2);
        return pi * r_min * r_min;
    }

    // حساب زوايا القطاعات
    double angle1 = 2 * acos((d * d + r1 * r1 - r2 * r2) / (2 * d * r1));
    double angle2 = 2 * acos((d * d + r2 * r2 - r1 * r1) / (2 * d * r2));

    // حساب مساحة القطاع - مثلث لكل دائرة
    double area1 = 0.5 * r1 * r1 * (angle1 - sin(angle1));
    double area2 = 0.5 * r2 * r2 * (angle2 - sin(angle2));

    return area1 + area2;
}
#include <iostream>
#include <cmath>
using namespace std;

const double pi = 3.141592653589793;

// دالة لحساب المسافة بين مركزين
double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// دالة لحساب مساحة الجزء المتقاطع بين دائرتين
double intersectionArea(double x1, double y1, double r1,
    double x2, double y2, double r2) {
    double d = distance(x1, y1, x2, y2);

    // لا يوجد تقاطع
    if (d >= r1 + r2) return 0;

    // إحدى الدائرتين داخل الأخرى بالكامل
    if (d <= abs(r1 - r2)) {
        double r_min = min(r1, r2);
        return pi * r_min * r_min;
    }

    // حساب زوايا القطاعات
    double angle1 = 2 * acos((d * d + r1 * r1 - r2 * r2) / (2 * d * r1));
    double angle2 = 2 * acos((d * d + r2 * r2 - r1 * r1) / (2 * d * r2));

    // حساب مساحة القطاع - مثلث لكل دائرة
    double area1 = 0.5 * r1 * r1 * (angle1 - sin(angle1));
    double area2 = 0.5 * r2 * r2 * (angle2 - sin(angle2));

    return area1 + area2;
}
