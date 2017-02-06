(define (queens board-size)
  (define (queen-cols k)  
    (if (= k 0)
        (list empty-board)
        (filter
         (lambda (positions) (safe? k positions))
         (flatmap
          (lambda (rest-of-queens)
            (map (lambda (new-row)
                   (adjoin-position new-row k rest-of-queens))
                 (enumerate-interval 1 board-size)))
          (queen-cols (- k 1))))))
  (queen-cols board-size))

(define empty-board ())
(define (adjoin-position new-row k rest-of-queens)
  (cons (list k new-row) rest-of-queens))
(define (safe? k positions)
  (define (in-check? queen1 queen2)
    (let ((horizontal-distance (abs (- (car queen1) (car queen2))))
          (vertical-distance (abs (- (cadr queen1) (cadr queen2)))))
    (or (= 0 vertical-distance)
        (= horizontal-distance vertical-distance))))
  (define (iter this-queen that-queens)
    (cond ((null? that-queens) true)
          ((in-check? this-queen (car that-queens))
             false)
          (else (iter this-queen (cdr that-queens)))))
  (iter (car positions) (cdr positions)))


