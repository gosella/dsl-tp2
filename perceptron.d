module perceptron;

struct Perceptron {
    alias tipo_callback = bool function(Perceptron p, double[][] X, int[] T, int n);

    this(int entradas, tipo_callback callback = null) {
        this.callback = callback;
        W.length =  entradas;
        reiniciar();
    }

    @property int entradas() const {
        return W.length;
    }

    void reiniciar() {
        W[] = 0;
        b = 0;
    }

    double[] W;
    double b;
    tipo_callback callback;

    int evaluar(double[] X) const {
        import std.numeric : dotProduct;
        return (dotProduct(X, W) + b) > 0;
    }

    int[] evaluar(double[][] X) const {
        import std.algorithm : map;
        import std.array : array;
        return map!(x => evaluar(x))(X).array;
    }

    int entrenar(double[][] X, int[] T, int max_pasos=1000) {
        import std.range : zip;

        foreach(n; 0 .. max_pasos) {
            bool entrenado = true;
            foreach(x, t; zip(X, T)) {
                auto y = evaluar(x);
                if (auto d = t - y) {
                    entrenado = false;
                    W[] += d * x[];
                    b += d;
                }
            }

            if ((callback != null && !callback(this, X, T, n)) || entrenado)
                return n;
        }
        return max_pasos;
    }
}
