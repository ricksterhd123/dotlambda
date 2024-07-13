; test object
(let ((a (make-test 3)))
    (display (+ (test->a a) 2))
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
