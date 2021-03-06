(define (detect-cycle x)
  (define (in-list? x l)
    (cond ((null? l) false)
          ((eq? x (car l)) true)
          (else (in-list? x (cdr l)))))
  (define (time-loop? past-days tomorrow)
    (cond ((null? tomorrow)
             false)
          ((in-list? tomorrow past-days)
             true)
          (else
             (time-loop? (cons tomorrow past-days)
                          (cdr tomorrow)))))
  (time-loop? '() x))
