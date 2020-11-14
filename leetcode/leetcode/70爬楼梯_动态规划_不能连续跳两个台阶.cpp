public int climbStarts(int n) {
        if(n == 1) return 1; // 防止数组溢出（f[2]）
        int[] f = new int[n+1];
        f[0] = 1;
        f[1] = 1;
        f[2] = 2;
        for(int i = 3; i <= n; i++) {
            f[i] = f[i-1] + f[i-3];
        }
        return f[n];
    }
