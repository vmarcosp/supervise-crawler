module Cleanfy = App__Cleanfy;
open TestFramework;

describe("Cleanfy", ({test}) => {
  describe("clean_value", ({test}) => {
    test("", ({expect}) => {
      let value = Cleanfy.clean_value(" teste  ");
      expect.string(value).toMatchSnapshot();
    })
  })
});
