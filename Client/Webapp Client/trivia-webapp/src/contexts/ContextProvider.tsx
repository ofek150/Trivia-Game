import React from "react";

type ProviderProps = {
  providers: React.ComponentType<any>[];
  children: React.ReactNode;
};

const ContextProvider: React.FC<ProviderProps> = ({ providers, children }) => {
  let renderedProviders = children;

  for (let i = providers.length - 1; i >= 0; i--) {
    const Provider = providers[i];
    renderedProviders = <Provider>{renderedProviders}</Provider>;
  }

  return <>{renderedProviders}</>;
};

export default ContextProvider;
