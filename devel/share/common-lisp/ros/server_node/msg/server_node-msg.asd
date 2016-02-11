
(cl:in-package :asdf)

(defsystem "server_node-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "status" :depends-on ("_package_status"))
    (:file "_package_status" :depends-on ("_package"))
  ))