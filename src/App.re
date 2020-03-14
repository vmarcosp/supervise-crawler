open Cohttp_lwt_unix
open Lwt
open Types

let get_final_url = response =>
      response
        |> Response.headers
        |> HttpUtils.get_location
        |> Base.Option.value(~default="")
        |> Url.with_suffix

let start_crawler = response => {
  open Cohttp_lwt;

  let%lwt (resp, body) = 
    response
      |>  get_final_url
      |>  HttpUtils.make_request

  let%lwt parsed_body = Body.to_string(body)

  Employee.get_data(parsed_body)
}

let execute = () => {
  let main = {
    let url = Url.create_url(10, 2018)
    
    let%lwt (response,_) = HttpUtils.make_request(url)

    start_crawler(response)
  }

  Lwt_main.run(main)
}
