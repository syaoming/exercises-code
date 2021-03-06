(define (same-parity . args)
  (let ((first (car args)))
  (define (sp-rec l)
    (cond ((null? l) l)
          ((even? (+ first (car l)))
             (cons (car l) (sp-rec (cdr l))))
          (else (sp-rec (cdr l)))))
  (cons first (sp-rec (cdr args)))))
