(define (count-pairs structure)
  (let ((checked-pairs '()))
  (define (checked? pair)
    (define (iter list)
      (cond ((null? list) false)
            ((eq? pair (car list)) true)
            (else (iter (cdr list)))))
    (iter checked-pairs))
  (define (count x)
    (if (or (not (pair? x))
            (checked? x))
        0
        (begin
          (set! checked-pairs (cons x checked-pairs))
          (+ (count (car x))
             (count (cdr x))
             1))))
  (count structure)))