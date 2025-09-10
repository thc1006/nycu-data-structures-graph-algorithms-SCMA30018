// 作業（一）實作 date 資料型態與其相關操作
// 作者：蔡秀吉 (H. C. Tsai)
// 電子信箱：hctsai@linux
// 日期：2025/09/09
// 請注意這份檔案僅是做為程式設計的邏輯參考，可能不完全符合老師的胃口（可能不會拿到滿分）
—

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

// 按照講義命名為小寫 "date"，並且遵循老師說的不可以用 std::chrono 來偷吃步
struct date
{
	int y;	// 年（Year）
	int m;	// 月（1..12）
	int d;	// 日（1~30/31 本程式碼後段邏輯包含 29 閏年）
};

// 月份與星期名：輸出用
static const char *MONTHS[12] = {
	"January","February","March","April","May","June",
	"July","August","September","October","November","December"
};

static const char *WEEK_SUN_TO_SAT[7] = {
	"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"
};

// 閏年判斷用：400/100/4 規則
static inline int is_leap(const int y)
{
	if (y % 400 == 0) return 1;
	if (y % 100 == 0) return 0;
	return (y % 4 == 0);
}

// 日期的有效性檢查，像門禁（沒有4月31號）無法通過就過不了就不給進 main
static int valid_date(const date &dt)
{
	if (dt.m < 1 || dt.m > 12) return 0;
	static const int md[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int lim = md[dt.m - 1];
	if (dt.m == 2 && is_leap(dt.y)) lim = 29;
	if (dt.d < 1 || dt.d > lim) return 0;
	return 1;
}

// 上網調研的方法 "Gregorian ↔ JDN（Fliegel–Van Flandern）"，可將公曆日期換成連續整數（JDN），加減就變成小學算術。時間複雜度 O(1)，跨世紀也穩。
static int64_t to_jdn(const int y0, const int m0, const int d0)
{
	int a = (14 - m0) / 12;
	int y = y0 + 4800 - a;
	int m = m0 + 12 * a - 3;
	int64_t j = d0 + (153 * m + 2) / 5 + 365LL * y + y / 4 - y / 100 + y / 400 - 32045;
	return j;
}

static void from_jdn(const int64_t j, int &y, int &m, int &d)
{
	// 把 JDN 還原為 (y,m,d)。配對是對稱的，不能改順序。
	int64_t a = j + 32044;
	int64_t b = (4 * a + 3) / 146097;
	int64_t c = a - (146097 * b) / 4;
	int64_t d1 = (4 * c + 3) / 1461;
	int64_t e = c - (1461 * d1) / 4;
	int64_t m1 = (5 * e + 2) / 153;
	d = (int)(e - (153 * m1 + 2) / 5 + 1);
	m = (int)(m1 + 3 - 12 * (m1 / 10));
	y = (int)(100 * b + d1 - 4800 + (m1 / 10));
}

// date ⇄ 連號（JDN）
static int64_t DateToSerial(const date &dt)
{
	return to_jdn(dt.y, dt.m, dt.d);
}

static date SerialToDate(const int64_t j)
{
	date out;
	from_jdn(j, out.y, out.m, out.d);
	return out;
}

// 月份名字；只有 1..12 會被呼叫。
static const char* MonthName(const int m)
{
	return MONTHS[m - 1];
}

// DayOfWeek(date)：回傳 Sunday..Saturday，這裡把 Sunday 調整成 0，對齊講義輸出。
static const char* DayOfWeek(const date &dt)
{
	int64_t j = DateToSerial(dt);
	// JDN 的模 7：常見對應是 Monday=0..Sunday=6，這裡加一 來 shift 讓 Sunday 變成等於 0
	int idx = (int)((j % 7 + 7) % 7);
	int idx2 = (idx + 1) % 7; // Sunday=0, Monday=1, ..., Saturday=6
	return WEEK_SUN_TO_SAT[idx2];
}

// DateSub(d1,d2)：回傳「從 d1 到 d2」的有號天數
// 另外，這裡的語意跟英文 from..to 一樣：b - a。
static int DateSub(const date &d1, const date &d2)
{
	int64_t a = DateToSerial(d1);
	int64_t b = DateToSerial(d2);
	int64_t diff = b - a; // signed
	// 防止極端溢位（幾乎用不到，但留著就像備用滅火器）
	if (diff < -(int64_t)0x7fffffff) diff = -(int64_t)0x7fffffff;
	if (diff >  (int64_t)0x7fffffff) diff =  (int64_t)0x7fffffff;
	return (int)diff;
}

// DateAdd(d,n)：回傳 d 之後 n 天；有了 JDN，這裡就變「加法作業」：序號 + n，再換回日期即可。
static date DateAdd(const date &d, const int n)
{
	int64_t base = DateToSerial(d);
	return SerialToDate(base + (int64_t)n);
}

// 輸出：MonthName dd, yyyy；規格要求的字面格式，逗號與空白都符合要求。
static void print_month_date_year(const date &dt)
{
	std::printf("%s %d, %d", MonthName(dt.m), dt.d, dt.y);
}

// optaional 的輸出工具：yyyy/mm/dd；講義寫「In addition to yyyy/mm/dd」，就字面上也要能印 y/m/d，所以就備著。
static void print_ymd(const date &dt)
{
	std::printf("%04d/%d/%d", dt.y, dt.m, dt.d);
}

// 解析三種輸入格式：小技巧：「看起來像區間」→「看起來像加法」→「看起來像單日」這個優先順序很順手；然後失敗就回 0，成功就回 1。
static int parse_line_type2(const char *s, date &a, date &b)
{
	// yyyy/mm/dd - YYYY/MM/DD   // '-' 兩側可接受有空白
	int y1,m1,d1,y2,m2,d2;
	if (std::sscanf(s, " %d/%d/%d - %d/%d/%d ", &y1,&m1,&d1,&y2,&m2,&d2) == 6)
	{
		a.y = y1; a.m = m1; a.d = d1;
		b.y = y2; b.m = m2; b.d = d2;
		return 1;
	}
	return 0;
}

static int parse_line_type3(const char *s, date &a, int &x)
{
	// yyyy/mm/dd + x   // x 可為負；"+ -65" 也算
	int y,m,d,k;
	if (std::sscanf(s, " %d/%d/%d + %d ", &y,&m,&d,&k) == 4)
	{
		a.y = y; a.m = m; a.d = d; x = k;
		return 1;
	}
	return 0;
}

static int parse_line_type1(const char *s, date &a)
{
	// yyyy/mm/dd
	int y,m,d;
	if (std::sscanf(s, " %d/%d/%d ", &y,&m,&d) == 3)
	{
		a.y = y; a.m = m; a.d = d;
		return 1;
	}
	return 0;
}

int main()
{
	// I/O 走「多筆直到 EOF」：遵照官教授網站提供的範例程式碼的格式。
	char buf[256];
	date d1, d2;

	while (std::fgets(buf, sizeof(buf), stdin))
	{
		// 關卡 1：區間（from..to）
		if (parse_line_type2(buf, d1, d2))
		{
			// 門禁：語法無效就不通過（避免印出怪日期）
			if (!valid_date(d1) || !valid_date(d2)) continue;

			int x = DateSub(d1, d2); // 有號天數：from d1 to d2
			std::printf("%d days from ", x);
			print_month_date_year(d1);
			std::printf(" to ");
			print_month_date_year(d2);
			std::printf(".\n");
			continue;
		}

		// 關卡 2：加法（after）
		int k = 0;
		if (parse_line_type3(buf, d1, k))
		{
			if (!valid_date(d1)) continue;

			date d3 = DateAdd(d1, k);
			std::printf("%d days after ", k);
			print_month_date_year(d1);
			std::printf(" is ");
			print_month_date_year(d3);
			std::printf(".\n");
			continue;
		}

		// 關卡 3：單日（is Weekday）
		if (parse_line_type1(buf, d1))
		{
			if (!valid_date(d1)) continue;

			const char *w = DayOfWeek(d1);
			print_month_date_year(d1);
			std::printf(" is %s.\n", w);
			continue;
		}

		// 其他：看不懂就裝死（沉默是金）。規格沒要報錯，我們就安靜忽略。
	}
	return 0;
}
