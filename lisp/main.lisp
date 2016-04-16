

(defun greet ()
	(format t "Hello, I am rouge, your dameaon. My goal is to improve your life"))


(defun get-the-time ()
	(format t "The time is."))


(defun tell-me-something ()
	(format t "Something"))

;;macro case-equal
;USAGE
;(case-equal item
;   ("a" (+ 2 1))
;   ("b" (+ 3 2))
;   (otherwise (+ 4 5)))
;
;EXPANDED
;(cond
;  ((equal "a" item) (+ 2 1))
;  ((equal "b" item) (+ 3 2))
;  (otherwise (+ 4 5)))

(defun tell-me-something-awesome ()
	(format t "What mood are you in?")
	(let ((mood (read-line *terminal-io*)))
		(cond 
			((equal "happy" mood) "Be generous in your actions, because you feel full")
			((equal "sad" mood) "Be grateful for the things you have")
			(t "I do not understand, but I love you regardless"))))

