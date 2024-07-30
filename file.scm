; test object
(let ((a (make-vector3 1 2 3)
      (b (make-vector3 1 2 3))))
    (display a)
    (newline)
)

(define update
    (lambda (dt)
        (display "Tick")
        (newline)
    )
)

(define draw
    (lambda ()
        (display "Frame")
        (newline)
    )
)
