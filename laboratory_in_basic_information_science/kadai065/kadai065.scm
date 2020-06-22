(define (find-min l)
  (if (null? (cddr l))
      (if (string<? (car l) (cadr l))
	  l
	  (cons (cadr l) (list (car l))))
      ((lambda (x)
	 (if (string<? (car l) (car x))
	     (cons (car l) x)
	     (cons (car x) (cons (car l) (cdr x)))))
       (find-min (cdr l)))))
(define (my-sort l)
  (if (null? (cdr l))
      l
      (let ((l (find-min l)))
	(cons (car l) (my-sort (cdr l))))))
  
