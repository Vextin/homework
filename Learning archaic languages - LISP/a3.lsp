;;  Austin Carlin  |  ajc0325 
;;  ROMAN NUMERAL - > NUMBER
;;
(defun r2d_digit (d) "Helper function to convert a single Roman digit into its decimal equivalent"
    (cond 
        ((null d) 0)
        ((eq d 'I) 1)
        ((eq d 'V) 5)
        ((eq d 'X) 10)
        ((eq d 'L) 50)
        ((eq d 'C) 100)
        ((eq d 'D) 500)
        ((eq d 'M) 1000)
    )
)


(defun romanToDecimal (romans) "Convert roman numerals to their decimal equivalent"
    
    (let ((total 0))
        ;;(write "Iterated")
        (setq curr ( r2d_digit (car romans) ) )
        (setq next ( r2d_digit (cadr romans) ) )
        (cond
            ( (= 0 curr)
                ;;(write "Null curr")
                (setq total 0)
            )

            ( (= 0 next) 
                ;;(write "Null next")
                (setq total curr)
            )

            ( (>= curr next)
                ;;(write ">= ")
                (setq total (+ total curr (romanToDecimal (cdr romans))))
            )

            ( ( < curr next)
                ;;(write "<")
                (setq total (+ total (- next curr) (romanToDecimal (cddr romans))))
            )
        )   
    )
)

;;
;;  COUNT FACTORIALS IN LIST AND SUBLISTS
;;

(defun rIsFactorial (n i) "Recursive part of isFactorial"
    (cond 
        ((= 1 n)
            1
        )
        ((= 0 (mod n i))
            (rIsFactorial (/ n i) (+ i 1))
        )
        ( t () 
            0
        )
    )


)

(defun isFactorial (n) "Helper function to check factorialness of a number"
    (let ((i 1))

        (rIsFactorial n i)

    )
)

(defun countFactorials (nList) 
    (let ((total 0))
        (cond
            ((not (or(numberp (car nList)) (listp (car nList))))
                NIL
            )
            ((null (car nList))
                ;(Write "zero")
                0
            )
            ((listp (car nList))
                ;(write "list")
                (setq total (+ total (countFactorials (car nList)) (countFactorials (cdr nList)) ))
            )
            ((= 1 (isFactorial (car nList)))
                ;(write "fac")
                (setq total (+ total 1 (countFactorials (cdr nList))))
            )
            ((= 0 (isFactorial (car nList)))
                ;(write "notFac")
                (setq total (+ total (countFactorials (cdr nList))))
            )

            total
        )
    )
)

;;
;;  MATCHING DNA SUBSETS
;;

(defun rFlipSet(set)
    (let ((c (car set)))
        (cond
            ((eq 'T c)
                (cons 'A (rFlipSet(cdr set)))
            )
            ((eq 'A c)
                (cons 'T (rFlipSet(cdr set)))
            )
            ((eq 'G c)
                (cons 'C (rFlipSet(cdr set)))
            )
            ((eq 'C c)
                (cons 'G (rFlipSet(cdr set)))
            )
        )
    )
)

(defun iMatchDNA () "Iterative part"
    ;(write working)
    ;(terpri)
    (cond 
        
        ((or  (null (caddr working) ) (equal (cadr working) orig))
            (write "done")
            working
        )
    
        ;;if a character matches, add that character to the match set, and remove it from the remainder set
        ((eq (car pat) (caaddr working))
            (setf working 
                (list 
                    (car working) 
                    (append (cadr working) (list(caaddr working)) )
                    (cdaddr working)
                )
            ) ;;put the first letter of the remainder into the match
            (setf pat (cdr pat))
            working
        )

        ;;if a character doesn't match, purge the contents of the match set into the before set.
        ((not (eq (car pat) (caaddr working)))
            (setf working 
                (list 
                    (append (append (car working) (cadr working)) (list(caaddr working))) 
                    () 
                    (cdaddr working)
                )
            )
            (setf pat orig)
            working
        )
    )
    (cond
        ((not (or  (null (caddr working) ) (equal (cadr working) orig)))
            ;;(write working)
            working
            (iMatchDNA)
        )
        ( t ()
            working
        )
    )  
)


(defun matchDNA (p s)
    ;(write s)
    ;;subset 1: before, subset 2: match, subset 3: after
    (defvar working '())
    (defvar pat ())
    (defvar orig ())
    (setf orig (rFlipSet p))
    (setf pat (rFlipSet p))
    (setf working (list '() '() s))
    ;(write working)
    (iMatchDNA)    
    ;working
    
)