(define (lookup given-key set-of-records)
  (if (null? set-of-records)
      false
      (let ((top-record (car set-of-records))
            (left-branch (cadr set-of-records))
            (right-branch (caddr set-of-records)))
        (let ((top-key (key top-record)))
          (cond ((equal? given-key top-key) top-record)
                ((< given-key top-key) (lookup given-key left-branch))
                (else (lookup given-key right-branch)))))))

;;; test code
(define key car)
(define a (list 1 'apple))
(define b (list 2 'banana))
(define c (list 3 'cherry))
(define test-tree (list b (list a '() '()) (list c '() '())))
(lookup 1 test-tree)
(lookup 2 test-tree)
(lookup 3 test-tree)
(newline)
