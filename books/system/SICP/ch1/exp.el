(+ 137 349)

(- 1000 334)

(* 5 99)

(/ 10 5)

(+ 2.7 10)

(* 2 ( + 1 3 ))

(+ 21 35 12 7)

(* 25 4 12)

(+ (* 3 5) (- 10 6))

(+ (* 3 (+ (* 2 4)
           (+ 3 5)))
   (+ (- 10 7) 6))

(define pi 3.14159)
pi
(define radius 10)
radius
(* pi (* radius radius))

(define circumference (* 2 pi radius))


(define A (* 5 5))
(* A A)

(define B (+ A (* 5 A)))


(define (square x) (* x x))
(square 10)


(defun average (x y )
  (/ (+ x y ) 2))

(average 5.0 10.0)
(defun mean-square (x y)
  (average (square x)
           (square y)))

(mean-square 2 3)


(defun ABS(x)
  (cond ((< x 0) (- x))
        ((= x 0) 0)
        ((> x 0) (x))))
(ABS -1)

(defun ABS(x)
  (if (< x 0)
      (- x)
    x))
(ABS 5)

(/ (+ 5 4 (- 2 (- 3 (+ 6 (/ 4.0 5.0)))))
   (* 3 (- 6 2) (- 2 7)))

(defun sos( x y )
  (+ (* x x )
     (* y y )))
(sos 1 2)
