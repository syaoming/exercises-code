(define (make-rat n d)
  (let ((g (if (< 0 d)
               (gcd n d)
               (- 0 (gcd n d)))))
  (cons (/ n g) (/ d g))))