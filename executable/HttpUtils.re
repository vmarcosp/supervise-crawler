let get_location = headers => Cohttp.Header.get(headers, "location")

let make_request = url => 
  url
  |> Uri.of_string
  |> Cohttp_lwt_unix.Client.get

let body_to_string = Cohttp_lwt.Body.to_string
