import React from "react";
import { RoomDataProvider } from "../contexts/RoomDataContext";
import Room from "../components/Room";

const RoomPage: React.FC = () => {
  return (
      <RoomDataProvider>
          <Room/>
      </RoomDataProvider>
  );
};

export default RoomPage;
