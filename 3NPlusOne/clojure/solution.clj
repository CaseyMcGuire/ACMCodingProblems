(require '[clojure.string :as str])

(defn naive-collatz
  "Returns the length of collatz chain for given number n"
  [n]
  (loop [num n
         chain-length 0]
    (let [new-chain-length (+ chain-length 1)
          mod-2? (== (mod num 2) 0)]
    (cond 
      (== num 1) new-chain-length
      mod-2? (recur (/ num 2) new-chain-length)
      :else (recur (+ (* 3 num) 1) new-chain-length)))))

(defn longest-collatz-chain
  "Returns the longest collatz chain that is found between begin and end"
  [begin end]
  (apply max (map naive-collatz (range begin end))))

(defn memo-longest-chain-length
  [begin end]
  (defn memoized-collatz
    "Calculate the length of collatz chain for n but check the chain-lengths map for previously 
  calculated chain lengths to avoid redundant calculations"
    [n chain-lengths]
    (loop [num n
           chain-length 0]
      (let [prev-calculated-chain (get chain-lengths num nil)
            new-chain-length (+ chain-length 1)
            mod-2? (== (mod num 2) 0)]
        (cond 
          prev-calculated-chain (+ prev-calculated-chain chain-length)
          (== num 1) new-chain-length
          mod-2? (recur (/ num 2) new-chain-length)
          :else (recur (+ (* 3 num) 1) new-chain-length)))))
  ;loop through each number in range to find longest chain
  (loop [cur-num begin
         lengths-calculated {}]
    (let [cur-chain-length (memoized-collatz cur-num lengths-calculated)
          updated-lengths-calculated (assoc lengths-calculated cur-num cur-chain-length)]
    (cond
      (== cur-num end) (apply max (vals lengths-calculated))
      :else (recur (+ cur-num 1) updated-lengths-calculated)))))

(doseq [line (line-seq (java.io.BufferedReader. *in*))]
  (let [[begin end] (map #(Integer/parseInt %) (str/split line #" "))]
    (println (str/join " " [begin end (memo-longest-chain-length begin end)]))))

