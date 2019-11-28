    //rate: 5.88 means 5.88%, amount: 100 means 100w 
    public static double binary(double rate, double amount) {
        rate /= 100;
        amount *= 10000;
        int n = 360;
        double left = 0, right = amount;

        for (int i = 0; i < 1000; i++) {
            double mid = (left + right) / 2;
            double remainAmount = amount;
            boolean flag = true;
            for (int j = 0; j < n; j++) {
                double interest = remainAmount * rate / 12;
                if (interest >= mid) {
                    flag = false;
                }
                if (interest > 0) {
                    remainAmount -= mid - interest;
                }
            }
            if (remainAmount <= 0 && flag) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return left;
    }
