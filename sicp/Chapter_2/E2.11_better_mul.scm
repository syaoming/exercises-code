(define (mul-interval x y)
  (let ((l-x (lower-bound x))
        (u-x (upper-bound x))
        (l-y (lower-bound y))
        (u-y (upper-bound y)))
  (cond ((positive? l-x) 
           (cond ((positive? l-y) (make-interval (* l-x l-y) (* u-x u-y)))
                 ((negative? u-y) (make-interval (* u-x l-y) (* l-x u-y)))
                 (else (make-interval (* u-x l-y) (* u-x u-y)))))
        ((negative? u-x)
           (cond ((positive? l-y) (make-interval (* l-x u-y) (* u-x l-y)))
                 ((negative? u-y) (make-interval (* u-x u-y) (* l-x l-y)))
                 (else (make-interval (* l-x u-y) (* l-x l-y)))))
        (else
           (cond ((positive? l-y) (make-interval (* l-x u-y) (* u-x u-y)))
                 ((negative? u-y) (make-interval (* u-x l-y) (* l-x l-y)))
                 (else (make-interval (min (* l-x u-y) (* u-x l-y))
                                      (max (* l-x l-y) (* u-y u-x)))))))))
