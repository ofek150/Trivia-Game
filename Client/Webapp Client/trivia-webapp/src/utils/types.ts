export interface LoginRequest {
  username: string;
  password: string;
}

export interface SignupRequest {
  username: string;
  password: string;
  email: string;
}

export interface GetPlayersInRoomRequest {
  roomId: number;
}

export interface JoinRoomRequest {
  roomId: number;
}

export interface CreateRoomRequest {
  roomName: string;
  maxUsers: number;
  questionCount: number;
  answerTimeout: number;
}

export interface SubmitAnswerRequest {
  answer: string;
}

export interface ParsedResponse {
  responseCode: number;
  data: any;
}

export interface RoomData {
  roomId: number,
  roomName: string;
  maxUsers: number;
  questionCount: number;
  answerTimeout: number;
  isActive: number;
  category: string;
}

export interface Rooms {
  rooms: Map<number, RoomData>;
}

export interface RoomState {
  hasGameBegan: boolean,
  players: String[],
  questionCount: number,
  answerTimeout: number
}

export interface Highscores {
  highscores : Object;
}

export interface GameData {
  question: string;
  answers: string[];
}
