import { CurrentRoomDataProvider } from "../contexts/CurrentRoomDataContext";
import Room from "../components/Room";


const RoomPage: React.FC = () => {
  return (
      <CurrentRoomDataProvider>
          <Room />
      </CurrentRoomDataProvider>
  );
};

export default RoomPage;
