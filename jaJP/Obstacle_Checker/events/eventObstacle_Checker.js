/*
 * Author: Tomo (@indiegdevstdio)
 * Given the tile position (X,Y), checks if there's any obstacles (collisions or actors) at that position
 */
const scriptValueHelpers = require("shared/lib/scriptValue/helpers");

export const id = "XV_TILE_MAP_OBSTACLE_CHECK";
export const name = "特定のタイルの障害物をチェックする";
export const groups = ["XV プラグイン"];

const fields = [].concat(
  [{
    type: "group",
    fields: [
      {
        label: "特定のタイル（X,Y）が通行可能かどうかをチェックします。指定したタイル上にアクターが存在せず、かつコリジョンが無い場合は、通行可能タイルとしてみなされます。「結果を保存する変数」には: 障害物なし=0、障害物あり=1 の値が入ります。",
        type: "label",
      },
    ],
  }],

  [{
    type: "group",
    fields: [
      {
        key: "x",
        type: "union",
        types: ["number", "variable"],
        label: "X",
        description: "チェック対象のマップの X 座標",
        width: "50%",
        unitsField: "units",
        unitsDefault: "tiles",
        unitsAllowed: ["tiles"],
        defaultType: "number",
        defaultValue: {
          number: 0,
          variable: "LAST_VARIABLE",
        },
      },
      {
        key: "y",
        type: "union",
        types: ["number", "variable"],
        label: "Y",
        description: "チェック対象のマップ Y 座標",
        width: "50%",
        unitsField: "units",
        unitsDefault: "tiles",
        unitsAllowed: ["tiles"],
        defaultType: "number",
        defaultValue: {
          number: 0,
          variable: "LAST_VARIABLE",
        },
      },
    ],
  }],

  [{
    type: "group",
    fields: [
      {
        key: "results",
        label: "結果を保存する変数",
        description: "コリジョン情報を保存する変数",
        type: "variable",
        defaultValue: "LAST_VARIABLE",
      },
    ],
  }],
);

export const compile = (input, helpers) => {
  console.log(input);
  const { x, y, results} = input;
  const { _stackPush, getVariableAlias, _stackPushConst, _callNative, _stackPop, appendRaw,
    variableSetToScriptValue, variableSetToValue, _stackPushReference } = helpers;
    const { precompileScriptValue, optimiseScriptValue } = scriptValueHelpers;

    // Get & push the value for tile X
    const [typeX] = precompileScriptValue(optimiseScriptValue(x));
    console.log(precompileScriptValue(optimiseScriptValue(x)));
    // Check if the passed tile X value is a number or variable
    if(typeX[0].type === "number") {
      // It was a number, so we push to stack as constant
      _stackPushConst(typeX[0].value);
      //console.log("X is Number: " + typeX[0].value);
    } else if(typeX[0].type === "variable") {
      // It was a variable, so we push to stack as variable
      const variableAlias = getVariableAlias(typeX[0].value);
      _stackPush(variableAlias);
      //console.log("X is Variable: " + typeX[0].value + " = " + variableAlias);
    } else {
      //console.log("Not supported type for X. Must be a number or a variable.");
      return;
    }

    // Get & push the value for tile Y
    const [typeY] = precompileScriptValue(optimiseScriptValue(y));
    console.log(precompileScriptValue(optimiseScriptValue(y)));

    // Check if the passed tile Y value is a number or variable
    if(typeY[0].type === "number") {
      // It was a number, so we push to stack as constant
      _stackPushConst(typeY[0].value);
      //console.log("Y is Number: " + typeY[0].value);
    } else if(typeY[0].type === "variable") {
      // It was a variable, so we push to stack as variable
      //const variableAlias = getVariableAlias(typeY[0].value);
      _stackPush(variableAlias);
      console.log("Y is Variable: " + typeY[0].value + " = " + variableAlias);
    } else {
      //console.log("Not supported type for Y. Must be a number or a variable.");
      _stackPop(1); // We already have value X pushed in stack, so remove it here
      return;
    }

    // Get & push the reference for variable results
    const [resultsVar] = precompileScriptValue(optimiseScriptValue(results));
    appendRaw(`VM_PUSH_REFERENCE ${getVariableAlias(resultsVar[0])}`);

    // Call native function on engine side
    _callNative("ObstacleChecker");
    // Remove pushed values from stack
    _stackPop(2);
    appendRaw(`VM_POP 1`);
};

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
};
