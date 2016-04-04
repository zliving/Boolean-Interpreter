<b>Boolean-Interpreter</b>
<p>This is a basic boolean interpreter that evaluates simple boolean expressions and retruns the result. </p>


<p><b>Syntax: </b>
<br>[B] ::= [IT].                               
<br>[IT] ::= [OT] [IT Tail]                     
<br>[IT Tail] ::= − ] [OT] [IT Tail]          
<br>::= ε 
<br>[OT] ::= [AT] [OT Tail] 
<br>[OT Tail] ::= ∨ [AT] [OT Tail] 
<br>::= ε 
<br>[AT] ::= [L] [AT Tail] 
<br>[AT Tail] ::= ∧ [L] [AT Tail] 
<br>::= ε 
<br>[L] ::= [A] 
<br>::= ∼ [L] 
<br>[A] ::= T
<br>::= F 
<br>::= ( [IT] )
</p>
<p><b>Syntactic Domains:</b>
<br>[B] : Bool stmt
<br>[IT] : Imply term
<br>[OT] : Or term
<br>[AT] : And term
<br>[IT Tail] : Imply tail
<br>[OT Tail] : Or tail
<br>[AT Tail] : And tail
<br>[L] : Literal
<br>[A] : Atom
</p>
<p><b>Semantic Domain:</b>
<br>b = {T.F} (Boolean values True and False)</p>

<p><b>Semantic Function Domains:</b>
<br>α : Bool stmt → b
<br>β : Imply term → b
<br>δ : Or term → b
<br>γ : And term → b
<br>λ : b × Imply tail → b
<br>µ : b × Or tail → b
<br>η : b × And tail → b
<br>φ : Literal → b
<br>ψ : Atom → b
</p>
<p>
<b>Semantic Equations:</b>
<br>α(<IT>.) = β(<IT>)
<br>β(<OT><IT Tail>) = λ(δ(<OT>),<IT Tail>)
<br>δ(<AT><OT Tail>) = µ(γ(<AT>),<OT Tail>)
<br>γ(<L><AT Tail>) = η(φ(<L>),<AT Tail>)
<br>λ(b, ε) = b (where b ∈ {T, F})
<br>λ(F, “− > ”<OT><IT Tail>) = λ(T,<IT Tail>)
<br>λ(T, “− > ”<OT><IT Tail>) = λ(δ(<OT>),<IT Tail>)
<br>µ(b, ε) = b (where b ∈ {T, F})
<br>µ(T, “ ∨ ”<AT><OT Tail>) = T
<br>µ(F, “ ∨ ”<AT><OT Tail>) = µ(γ(<AT>),<OT Tail>)
<br>η(b, ε) = b (where b ∈ {T, F})
<br>η(F, “ ∧ ”<L><AT Tail>) = F
<br>η(T, “ ∧ ”<L><AT Tail>) = η(φ(<L>),<AT Tail>)
<br>φ(“ ∼ ”<L>) = if φ(<L>) = T then F else if φ(<L>) = F then T
<br>φ(<A>) = ψ(<A>)
<br>ψ(“T”) = T
<br>ψ(“F”) = F
<br>ψ(“(”<IT>“)”) = (β(<IT>))
</p>

Credits:
Interpreter written by: Zach Livingston
Syntax and Semantics written by: Dr.Richard Watson
