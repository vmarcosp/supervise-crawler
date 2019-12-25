let withDefault = (option, defaultValue) => 
  Base.(
    option
      |>Option.value(~default=defaultValue)
  )
  
let (@?>) = withDefault
