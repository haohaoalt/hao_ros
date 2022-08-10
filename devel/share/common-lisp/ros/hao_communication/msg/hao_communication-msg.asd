
(cl:in-package :asdf)

(defsystem "hao_communication-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "PersonMsg" :depends-on ("_package_PersonMsg"))
    (:file "_package_PersonMsg" :depends-on ("_package"))
  ))